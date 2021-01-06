#include "Scene.h"

Scene::Scene() {
	printf("Creating room");
	createRoom();
}

Scene::~Scene()
{
	for (size_t i = 0; i < _objects.size(); i++)
	{
			delete _objects[i];
	}
}

// Loop over all objects in the scene and detect ray intersections
bool Scene::castRay(Ray& ray) {
	
	for (Triangle triangle : _triangles) {
		triangle.rayIntersection(ray);
	}
	
	for (Object* object : _objects) {
		object->rayIntersection(ray);
	}

	//for (Tetrahedron tetrahedron : _tetrahedrons) {
	//	tetrahedron.rayIntersection(ray);
	//}

	//for (Sphere sphere : _spheres) {
	//	sphere.rayIntersection(ray);
	//}

	for (LightSource light : _lightSources) {
		light.rayIntersection(ray);
	}

	if (ray.hasIntersection())
		return true;
	else
		return false;
}

ColorDbl Scene::castShadowRay(const Vertex& origin, const Direction& normal) {
	// Initial light contribution is zero (since light contribtuion is applied additatively)
	ColorDbl lightContribution(0.0);
	
	int lightCount = 0;			// Numer of light sources / light triangles we cast shadow rays towards
	double lightArea = 0.0;		// Area of light sources taken into account

	for(LightSource light : _lightSources) {
		for (Triangle lightTriangle : light.getTriangles()) {
			lightArea += lightTriangle.getArea();	
			/* Each iteration of the loop below will change the random point on the light source
			 * which might add to the light contribution if the origin can only partially see the
			 * light source. Thus, a higher shadow ray count should increase the brightness in the scene */ 
			for (int i = 0; i < SHADOW_RAY_COUNT; i++) {
				++lightCount;

				Vertex lightPoint = lightTriangle.getRandomPoint();

				// Create a shadow ray towards our light source
				Ray shadowRay(origin + (Vertex(normal, 0.0) * 0.1f), lightPoint);
				this->castRay(shadowRay);

				// Does the shadow ray have a direct line of sight to the point on the light source?
				if (shadowRay.hasIntersection() && shadowRay.getIntersectionMaterial() == LIGHT_SOURCE) {
					Direction lightNormal = shadowRay.getIntersectionNormal();
					Direction shadowRayDir = glm::normalize(shadowRay.getEnd() - shadowRay.getStart());

					// Since both vectors are normalized, the dot product returns the cosine between the two vectors
					// Negative means that the shadow ray and light source are facing eachother which means that we still want that sweet contribution
					double dt = glm::abs(glm::dot(shadowRayDir, lightNormal));

					lightContribution += shadowRay.getColor() * dt;
				}

				// Old code that does not work...
				//if(shadowRay.hasIntersection() && shadowRay.getClosestIntersection() < glm::distance(origin, lightPoint))
				//{
				//	// Not visible, so no light contribution
				//	continue;
				//}

				//Direction shadowRayDirection = glm::normalize(shadowRay.getEnd() - shadowRay.getStart());
				//double alpha = glm::dot(-normal, shadowRayDirection);	
				//double beta = glm::clamp((double)glm::dot(lightTriangle.getNormal(), -shadowRayDirection), 0.0, 1.0);

				//double geometric = alpha * beta / pow(glm::distance(origin, lightPoint), 2.0);
				//lightContribution += lightTriangle.getColor() * light.getEmission() * geometric;
				
			}
		}
	}

	return lightContribution * lightArea / (double)lightCount;
}

void Scene::addLightsource(LightSource& lightsource) {
	_lightSources.push_back(lightsource);
}

void Scene::addObject(Object* object) 
{
	_objects.push_back(object);
}

void Scene::createRoom() {
	_vertices =
	{
		Vertex(0.0f, 6.0f, 5.0f, 1.0f),		//  (0)		d-top
		Vertex(0.0f, 6.0f, -5.0f, 1.0f),	//	(1)		d-bottom
		Vertex(10.0f, 6.0f, 5.0f, 1.0f),	//	(2)		b-top
		Vertex(10.0f, 6.0f, -5.0f, 1.0f),	//	(3)		b-bottom
		Vertex(13.0f, 0.0f, 5.0f, 1.0f),	//	(4)		a-top
		Vertex(13.0f, 0.0f, -5.0f, 1.0f),	//	(5)		a-bottom
		Vertex(10.0f, -6.0f, 5.0f, 1.0f),	//	(6)		c-top
		Vertex(10.0f, -6.0f, -5.0f, 1.0f),	//	(7)		c-bottom
		Vertex(0.0f, -6.0f, 5.0f, 1.0f),	//	(8)		e-top
		Vertex(0.0f, -6.0f, -5.0f, 1.0f),	//	(9)		e-bottom
		Vertex(-3.0f, 0.0f, 5.0f, 1.0f),	//	(10)	f-top
		Vertex(-3.0f, 0.0f, -5.0f, 1.0f),	//	(11)	f-bottom
		Vertex(5.0f, 0.0f, 5.0f, 1.0f),		//	(12)
		Vertex(5.0f, 0.0f, -5.0f, 1.0f)		//	(13)
	};

	// The scene viewed from above:
	// ^ = Camera 1 and its viewing direction (origo)
	// v = camera 2 and its viewing direction
	//           a
	//        /     \    <--- FRONT
	//LEFT	b    v    c  RIGHT
	//      |         |  <--- CENTER
	//      d    ^    e
	//        \     /    <--- BACK
	//			 f
	//           
	//			 ^ x-direction
	//           | 
	//       <---|  y-direction
	//		z-direction UPWARDS
	
	const ColorDbl Red = ColorDbl(240, 0, 0);
	const ColorDbl Green = ColorDbl(0, 240, 0);
	const ColorDbl Blue = ColorDbl(0, 0, 240);
	const ColorDbl White = ColorDbl(255, 255, 255);

	//Floor (normals point up)
	_triangles.push_back(Triangle(_vertices.at(3), _vertices.at(7), _vertices.at(5), White));
	_triangles.push_back(Triangle(_vertices.at(3), _vertices.at(1), _vertices.at(7), White));
	_triangles.push_back(Triangle(_vertices.at(1), _vertices.at(9), _vertices.at(7), White));
	_triangles.push_back(Triangle(_vertices.at(1), _vertices.at(11), _vertices.at(9), White));
	//Roof (normals point down)
	_triangles.push_back(Triangle(_vertices.at(2), _vertices.at(4), _vertices.at(6), White));
	_triangles.push_back(Triangle(_vertices.at(2), _vertices.at(6), _vertices.at(0), White));
	_triangles.push_back(Triangle(_vertices.at(0), _vertices.at(6), _vertices.at(8), White));
	_triangles.push_back(Triangle(_vertices.at(0), _vertices.at(8), _vertices.at(10), White));
	//Left middle (normals point right)
	_triangles.push_back(Triangle(_vertices.at(3), _vertices.at(2), _vertices.at(0), Green));
	_triangles.push_back(Triangle(_vertices.at(3), _vertices.at(0), _vertices.at(1), Green));
	//Left front (normals point right)
	_triangles.push_back(Triangle(_vertices.at(5), _vertices.at(4), _vertices.at(2), Green));
	_triangles.push_back(Triangle(_vertices.at(5), _vertices.at(2), _vertices.at(3), Green));
	//Left back (normals point right)
	_triangles.push_back(Triangle(_vertices.at(1), _vertices.at(0), _vertices.at(10), Green));
	_triangles.push_back(Triangle(_vertices.at(1), _vertices.at(10), _vertices.at(11), Green));
	//Right middle (normals pointing left)
	_triangles.push_back(Triangle(_vertices.at(9), _vertices.at(8), _vertices.at(6), Blue));
	_triangles.push_back(Triangle(_vertices.at(9), _vertices.at(6), _vertices.at(7), Blue));
	//Right front (normals pointing left)
	_triangles.push_back(Triangle(_vertices.at(7), _vertices.at(6), _vertices.at(4), Blue));
	_triangles.push_back(Triangle(_vertices.at(7), _vertices.at(4), _vertices.at(5), Blue));
	//Right back (normals pointing left)
	_triangles.push_back(Triangle(_vertices.at(11), _vertices.at(10), _vertices.at(8), Red));
	_triangles.push_back(Triangle(_vertices.at(11), _vertices.at(8), _vertices.at(9), Red));

	// Set the material of all triangles making up the room to diffuse
	for (size_t i = 0; i < _triangles.size(); i++) {
		_triangles[i].updateMaterial(0);
	}
}