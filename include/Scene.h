#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <vector>
#include "Triangle.h"

struct TriangleIntersection {
	Triangle triangle;
	Vertex point;
};

class Scene {
public:
	Scene();
	void createRoom();
	std::list<TriangleIntersection> detectIntersections(Ray ray) const;
private:
	std::vector<Triangle> triangles;
};

#endif // !SCENE_H