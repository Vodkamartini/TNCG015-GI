#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <vector>
#include "Triangle.h"
#include "Tetrahedron.h"
#include "ImplicitSphere.h"

//using Intersection = std::pair<Triangle, Vertex>;

class Scene {
public:
	Scene();
	~Scene() {};
	void createRoom();
	void createTestRoom();
	void addTetrahedron();
	void addImplicitSphere();
	bool detectIntersection(Ray ray) const;

	size_t getTriangles() {
		return triangles.size();
	}

	size_t getImplicitSpheres() {
		return spheres.size();
	}

private:
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
	std::vector<ImplicitSphere> spheres;
};

#endif // !SCENE_H