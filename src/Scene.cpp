#include "Scene.h"

Scene::Scene() {
	//createRoom();
}

/* Determines which Triangle is intersected by the ray by calling
 * rayIntersection for each Triangle in the scene. It then passes references
 * to the Triangle and the intersection point to the ray. */
bool Scene::detectIntersection(Ray ray) const {

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
	const ColorDbl Red = ColorDbl(240, 0, 0);
	const ColorDbl Green = ColorDbl(0, 240, 0);
	const ColorDbl Blue = ColorDbl(0, 0, 240);
	const ColorDbl White = ColorDbl(255, 255, 255);

	//Floor (normals point up)
	triangles.push_back(Triangle(vertices.at(3), vertices.at(7), vertices.at(5), White));
	triangles.push_back(Triangle(vertices.at(3), vertices.at(1), vertices.at(7), White));
	triangles.push_back(Triangle(vertices.at(1), vertices.at(9), vertices.at(7), White));
	triangles.push_back(Triangle(vertices.at(1), vertices.at(11), vertices.at(9), White));

	//Roof (normals point down)
	triangles.push_back(Triangle(vertices.at(2), vertices.at(4), vertices.at(6), White));
	triangles.push_back(Triangle(vertices.at(2), vertices.at(6), vertices.at(0), White));
	triangles.push_back(Triangle(vertices.at(0), vertices.at(6), vertices.at(8), White));
	triangles.push_back(Triangle(vertices.at(0), vertices.at(8), vertices.at(10), White));

	//Left middle (normals point right)
	triangles.push_back(Triangle(vertices.at(3), vertices.at(2), vertices.at(0), Green));
	triangles.push_back(Triangle(vertices.at(3), vertices.at(0), vertices.at(1), Green));

	//Left front (normals point right)
	triangles.push_back(Triangle(vertices.at(5), vertices.at(4), vertices.at(2), Green));
	triangles.push_back(Triangle(vertices.at(5), vertices.at(2), vertices.at(3), Green));

	//Left back (normals point right)
	triangles.push_back(Triangle(vertices.at(1), vertices.at(0), vertices.at(10), Green));
	triangles.push_back(Triangle(vertices.at(1), vertices.at(10), vertices.at(11), Green));

	//Right middle (normals pointing left)
	triangles.push_back(Triangle(vertices.at(9), vertices.at(8), vertices.at(6), Blue));
	triangles.push_back(Triangle(vertices.at(9), vertices.at(6), vertices.at(7), Blue));

	//Right front (normals pointing left)
	triangles.push_back(Triangle(vertices.at(7), vertices.at(6), vertices.at(4), Blue));
	triangles.push_back(Triangle(vertices.at(7), vertices.at(4), vertices.at(5), Blue));

	//Right back (normals pointing left)
	triangles.push_back(Triangle(vertices.at(11), vertices.at(10), vertices.at(8), Red));
	triangles.push_back(Triangle(vertices.at(11), vertices.at(8), vertices.at(9), Red));



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
	ImplicitSphere sphere = ImplicitSphere(2.0f, Vertex(6.0f, -4.0f, 3.0f, 1.0f), ColorDbl(0,130,130));
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

	ColorDbl Yellow = ColorDbl(0, 255, 255);

	triangles.push_back(Triangle(vertices.at(1), vertices.at(2), vertices.at(1), Yellow));
	triangles.push_back(Triangle(vertices.at(1), vertices.at(3), vertices.at(2), Yellow));


}