#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <vector>
#include "Triangle.h"

using Intersection = std::pair<Triangle, Vertex>;

class Scene {
public:
	Scene();
	~Scene() {};
	void createRoom();
	void createTestRoom();
	Intersection detectIntersection(Ray ray) const;

	int getTriangles() {
		return triangles.size();
	}

private:
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
};

#endif // !SCENE_H