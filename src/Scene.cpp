#include "Scene.h"

Scene::Scene() {
	createRoom();
}

void Scene::importTriangle(Triangle& t) {
	triangles.push_back(t);
}

void Scene::importTriangles(std::vector<Triangle> triangles) {
	for each (Triangle t in triangles)
	{
		Scene::importTriangle(t);
	}
}

void Scene::importLightSource(LightSource& l) {
	lightsources.push_back(l);
}

void Scene::importLightSources(std::vector<LightSource> lightSources) {
	for each (LightSource l in lightSources)
	{
		Scene::importLightSource(l);
	}
}

std::list<TriangleIntersection> Scene::detectIntersections(Ray ray) const {
	std::list<TriangleIntersection> intersections = {};
	for each (Triangle t in triangles)
	{
		TriangleIntersection ti;
		Vertex intersection;
		if (t.intersection(ray, intersection) == INTERSECTION)
		{
			// If the point intersects the triangle, add them to ti and push_back list
			ti.triangle = t;
			ti.point = intersection;
			intersections.push_back(ti);
		}
	}
	// Might want to add some sort of margin for intersection
	return intersections;
}

ColorDb Scene::getLightContribution(const Vertex& point, const Direction& normal) const {

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
				

	Vertex aTop(-3.0f,0.0f,5.0f), aBottom(-3.0f,0.0f,-5.0f);
	Vertex bTop(0.0f,-6.0f,5.0f), bBottom(0.0f,-6.0f,-5.0f);
	Vertex cTop(0.0f, 6.0f, 5.0f), cBottom(0.0f, 6.0f, -5.0f);
	Vertex dTop(10.0f, -6.0f, 5.0f), dBottom(10.0f, -6.0f, -5.0f);
	Vertex eTop(10.0f, 6.0f, 5.0f), eBottom(10.0f, 6.0f, -5.0f);
	Vertex fTop(13.0f, 0.0f, 5.0f), fBottom(13.0f, 0.0f, -5.0f);

	const Surface Red = Surface(ColorDb(255, 0, 0));
	const Surface Green = Surface(ColorDb(0, 255, 0));
	const Surface White = Surface(ColorDb(255, 255, 255));
	
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
