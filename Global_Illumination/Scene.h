#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "utils.h"
#include "Triangle.h"
#include "LightSource.h"
#include "Object.h"

class Scene
{
public:
	Scene();
	~Scene();

	bool castRay(Ray& ray, size_t depth);
	ColorDbl castShadowRay(const Vertex& origin, const Direction& normal);

	void addObject(Object* object);
	//void addTetrahedron(Tetrahedron& tetrahedron);
	//void addSphere(Sphere& sphere);
	void addLightsource(LightSource& lightsource);
private:
	void createRoom();


	std::vector<Object*> _objects;

	std::vector<Triangle> _triangles;
	std::vector<Vertex> _vertices;
	//std::vector<Tetrahedron> _tetrahedrons;
	//std::vector<Sphere> _spheres;
	std::vector<LightSource> _lightSources;
};

#endif // !SCENE_H




