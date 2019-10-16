#include "Scene.h"

Scene::Scene() {
	createRoom();
}

/* Determines which Triangle is intersected by the ray by calling
 * rayIntersection for each Triangle in the scene. It then passes references
 * to the Triangle and the intersection point to the ray. */
Intersection Scene::detectIntersection(Ray ray) const {
	Intersection ti = std::make_pair(Triangle(), Vertex(0));

	for (Triangle triangle : triangles) {

		Vertex intersection;
		if (triangle.rayIntersection(ray, intersection) == INTERSECTION) {
			ti.first= triangle;
			ti.second = intersection;
		}
	}

	return ti;
}

void Scene::createRoom() {
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
	//			 ^ z direction
	//           | 
	//           |-----> x direction


	Vertex aTop(-3.0f, 0.0f, 5.0f, 0.0), aBottom(-3.0f, 0.0f, -5.0f, 0.0);
	Vertex bTop(0.0f, -6.0f, 5.0f, 0.0), bBottom(0.0f, -6.0f, -5.0f, 0.0);
	Vertex cTop(0.0f, 6.0f, 5.0f, 0.0), cBottom(0.0f, 6.0f, -5.0f, 0.0);
	Vertex dTop(10.0f, -6.0f, 5.0f, 0.0), dBottom(10.0f, -6.0f, -5.0f, 0.0);
	Vertex eTop(10.0f, 6.0f, 5.0f, 0.0), eBottom(10.0f, 6.0f, -5.0f, 0.0);
	Vertex fTop(13.0f, 0.0f, 5.0f, 0.0), fBottom(13.0f, 0.0f, -5.0f, 0.0);

	const ColorDbl Red = ColorDbl(255, 0, 0);
	const ColorDbl Green = ColorDbl(0, 255, 0);
	const ColorDbl White = ColorDbl(255, 255, 255);

	//Floor
	triangles.push_back(Triangle(bBottom, cBottom, aBottom, White));
	triangles.push_back(Triangle(bBottom, dBottom, cBottom, White));
	triangles.push_back(Triangle(dBottom, eBottom, cBottom, White));
	triangles.push_back(Triangle(dBottom, fBottom, eBottom, White));

	//Roof
	triangles.push_back(Triangle(bTop, cTop, aTop, White));
	triangles.push_back(Triangle(bTop, dTop, cTop, White));
	triangles.push_back(Triangle(dTop, eTop, cTop, White));
	triangles.push_back(Triangle(dTop, fTop, eTop, White));

	//Left middle
	triangles.push_back(Triangle(bTop, bBottom, dBottom, Red));
	triangles.push_back(Triangle(dBottom, dTop, bTop, Red));

	//Left front
	triangles.push_back(Triangle(aTop, aBottom, bBottom, Red));
	triangles.push_back(Triangle(bBottom, bTop, aTop, Red));

	//Left back
	triangles.push_back(Triangle(dTop, dBottom, fBottom, Red));
	triangles.push_back(Triangle(fBottom, fTop, dTop, Red));

	//Right middle
	triangles.push_back(Triangle(cTop, cBottom, eBottom, Green));
	triangles.push_back(Triangle(eBottom, eTop, cTop, Green));

	//Right front
	triangles.push_back(Triangle(aTop, aBottom, cBottom, Green));
	triangles.push_back(Triangle(cBottom, cTop, aTop, Green));

	//Right back
	triangles.push_back(Triangle(eTop, eBottom, fBottom, White));
	triangles.push_back(Triangle(fBottom, fTop, eTop, White));
}