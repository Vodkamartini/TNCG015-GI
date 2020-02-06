#include "Scene.h"


const ColorDbl Yellow = ColorDbl(255, 211, 0);
const ColorDbl Red = ColorDbl(240, 0, 0);
const ColorDbl Green = ColorDbl(0, 240, 0);
const ColorDbl Blue = ColorDbl(0, 0, 240);
const ColorDbl White = ColorDbl(255, 255, 255);

const Material YellowMaterial = Material(Yellow, PERFECT_REFLECTOR, glm::vec3(1.0f), 1.0f);
const Material RedMaterial = Material(Red, LAMBERTIAN, glm::vec3(0.f), 1.0f);
const Material GreenMaterial = Material(Green, LAMBERTIAN, glm::vec3(0.f), 1.0f);
const Material BlueMaterial = Material(Blue, LAMBERTIAN, glm::vec3(0.f), 1.0f);
const Material WhiteMaterial = Material(White, LAMBERTIAN, glm::vec3(0.f), 1.0f);

Scene::Scene() {
	//createRoom();
}

/* Determines which Triangle is intersected by the ray by calling
 * rayIntersection for each Triangle in the scene. It then passes references
 * to the Triangle and the intersection point to the ray. */
bool Scene::detectIntersection(Ray& ray) const {

	for (Triangle triangle : triangles) {
		triangle.rayIntersection(ray);
	}

	for (ImplicitSphere sphere : spheres) {
		sphere.rayIntersection(ray);
	}

	if (!ray.hasIntersection()) {
		ray.setIntersection(Intersection());
		return false;
	}

	ray.setColor(ray.getIntersection().color);
	return true;
}

void Scene::createRoom() {

	vertices =
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


	//Floor (normals point up)
	triangles.push_back(Triangle(vertices.at(3), vertices.at(7), vertices.at(5), WhiteMaterial));
	triangles.push_back(Triangle(vertices.at(3), vertices.at(1), vertices.at(7), WhiteMaterial));
	triangles.push_back(Triangle(vertices.at(1), vertices.at(9), vertices.at(7), WhiteMaterial));
	triangles.push_back(Triangle(vertices.at(1), vertices.at(11), vertices.at(9), WhiteMaterial));

	//Roof (normals point down)
	triangles.push_back(Triangle(vertices.at(2), vertices.at(4), vertices.at(6), WhiteMaterial));
	triangles.push_back(Triangle(vertices.at(2), vertices.at(6), vertices.at(0), WhiteMaterial));
	triangles.push_back(Triangle(vertices.at(0), vertices.at(6), vertices.at(8), WhiteMaterial));
	triangles.push_back(Triangle(vertices.at(0), vertices.at(8), vertices.at(10), WhiteMaterial));

	//Left middle (normals point right)
	triangles.push_back(Triangle(vertices.at(3), vertices.at(2), vertices.at(0), GreenMaterial));
	triangles.push_back(Triangle(vertices.at(3), vertices.at(0), vertices.at(1), GreenMaterial));

	//Left front (normals point right)
	triangles.push_back(Triangle(vertices.at(5), vertices.at(4), vertices.at(2), GreenMaterial));
	triangles.push_back(Triangle(vertices.at(5), vertices.at(2), vertices.at(3), GreenMaterial));

	//Left back (normals point right)
	triangles.push_back(Triangle(vertices.at(1), vertices.at(0), vertices.at(10), GreenMaterial));
	triangles.push_back(Triangle(vertices.at(1), vertices.at(10), vertices.at(11), GreenMaterial));

	//Right middle (normals pointing left)
	triangles.push_back(Triangle(vertices.at(9), vertices.at(8), vertices.at(6), BlueMaterial));
	triangles.push_back(Triangle(vertices.at(9), vertices.at(6), vertices.at(7), BlueMaterial));

	//Right front (normals pointing left)
	triangles.push_back(Triangle(vertices.at(7), vertices.at(6), vertices.at(4), BlueMaterial));
	triangles.push_back(Triangle(vertices.at(7), vertices.at(4), vertices.at(5), BlueMaterial));

	//Right back (normals pointing left)
	triangles.push_back(Triangle(vertices.at(11), vertices.at(10), vertices.at(8), RedMaterial));
	triangles.push_back(Triangle(vertices.at(11), vertices.at(8), vertices.at(9), RedMaterial));

	/*
	Vertex aTop(-3.0f, 0.0f, 5.0f, 1.0), aBottom(-3.0f, 0.0f, -5.0f, 1.0);
	Vertex bTop(0.0f, -6.0f, 5.0f, 1.0), bBottom(0.0f, -6.0f, -5.0f, 1.0);
	Vertex cTop(0.0f, 6.0f, 5.0f,  1.0), cBottom(0.0f, 6.0f, -5.0f,  1.0);
	Vertex dTop(10.0f, -6.0f, 5.0f,1.0), dBottom(10.0f, -6.0f, -5.0f,1.0);
	Vertex eTop(10.0f, 6.0f, 5.0f, 1.0), eBottom(10.0f, 6.0f, -5.0f, 1.0);
	Vertex fTop(13.0f, 0.0f, 5.0f, 1.0), fBottom(13.0f, 0.0f, -5.0f, 1.0);
	*/
}

void Scene::addTetrahedron() {
	Tetrahedron tetra = Tetrahedron();
	for each (Triangle t in tetra.getTriangles())
	{
		triangles.push_back(t);
	}
}

void Scene::addImplicitSphere() {
	ImplicitSphere sphere = ImplicitSphere(1.0f, Vertex(5.f, -3.f, 2.f, 0.0f), YellowMaterial);
	spheres.push_back(sphere);
}

void Scene::createTestRoom() {
	vertices =
	{
		Vertex(10.0f, -6.0f, 5.0f, 1.0f),	//	(0)		c-top
		Vertex(10.0f, -6.0f, -5.0f, 1.0f),	//	(1)		c-bottom
		Vertex(10.0f, 6.0f, 5.0f, 1.0f),	//	(2)		b-top
		Vertex(10.0f, 6.0f, -5.0f, 1.0f),	//	(3)		b-bottom
	};

	ColorDbl Yellow = ColorDbl(255, 211, 0);

	//triangles.push_back(Triangle(vertices.at(1), vertices.at(2), vertices.at(1), Yellow));
	//triangles.push_back(Triangle(vertices.at(1), vertices.at(3), vertices.at(2), Yellow));


}