#include "Scene.h"

Scene::Scene() {
	printf("Creating room");
	createRoom();
}

// Loop over all objects in the scene and detect ray intersections
bool Scene::castRay(Ray& ray) {
	
	for (Triangle triangle : _triangles) {
		triangle.rayIntersection(ray);
	}

	for (Tetrahedron tetrahedron : _tetrahedrons) {
		tetrahedron.rayIntersection(ray);
	}

	for (Sphere sphere : _spheres) {
		sphere.rayIntersection(ray);
	}

	for (LightSource light : _lightSources) {
		light.rayIntersection(ray);
	}

	if (ray.hasIntersection())
		return true;
	else
		return false;
}

ColorDbl Scene::castShadowRay(const Vertex& origin, const Direction& normal) {
	ColorDbl lightContribution(0.0);
	
	int lightCount = 0;
	double lightArea = 0.0;

	for(LightSource light : _lightSources) {
		for (Triangle lightTriangle : light.getTriangles()) {
			lightArea += lightTriangle.getArea();	
			for (int i = 0; i < SHADOW_RAY_COUNT; i++) {
				++lightCount;

				Vertex lightPoint = lightTriangle.getRandomPoint();

				// Create a shadow ray towards our light source
				Ray shadowRay(origin, glm::normalize(lightPoint - origin));

				// Detect all intersections towards light source
				// If closest intersection is closer than light, point is occluded
				this->castRay(shadowRay);
				if(!shadowRay.hasIntersection() || shadowRay.getClosestIntersection() < glm::distance(origin, lightPoint))
				{
					// Not visible, so no light contribution
					continue;
				}

				Direction shadowRayDirection = glm::normalize(shadowRay.getEnd() - shadowRay.getStart());
				double alpha = glm::dot(normal, shadowRayDirection);	
				double beta = glm::clamp((double)glm::dot(lightTriangle.getNormal(), -shadowRayDirection), 0.0, 1.0);

				double geometric = alpha * beta / pow(glm::distance(origin, lightPoint), 2.0);
				lightContribution += lightTriangle.getColor() * light.getEmission() * geometric;
				
			}
		}
	}

	return lightContribution * lightArea / (double)lightCount;
}

void Scene::addTetrahedron(Tetrahedron& tetrahedron) {
	_tetrahedrons.push_back(tetrahedron);
}

void Scene::addSphere(Sphere& sphere) {
	_spheres.push_back(sphere);
}

void Scene::addLightsource(LightSource& object) {
	_lightSources.push_back(object);
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
}