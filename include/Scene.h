#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <vector>
#include "Triangle.h"
/*
struct TriangleIntersection {
	Triangle triangle;
	Vertex point = Vertex(0);
}; */

using Intersection = std::pair<Triangle, Vertex>;

class Scene {
public:
	Scene();
	~Scene() {};
	void createRoom();
	Intersection detectIntersection(Ray ray) const;
private:
	std::vector<Triangle> triangles;
};

#endif // !SCENE_H