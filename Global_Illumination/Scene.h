#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "utils.h"
#include "Triangle.h"
#include "LightSource.h"
#include "Tetrahedron.h"
#include "Sphere.h"

class Scene
{
public:
	Scene();

	bool castRay(Ray& ray);
	ColorDbl castShadowRay(const Vertex& origin, const Direction& normal);
	void addTetrahedron(Tetrahedron& tetrahedron);
	void addSphere(Sphere& sphere);
	void addLightsource(LightSource& object);
private:
	void createRoom();

	std::vector<Triangle> _triangles;
	std::vector<Vertex> _vertices;
	std::vector<Tetrahedron> _tetrahedrons;
	std::vector<Sphere> _spheres;
	std::vector<LightSource> _lightSources;
};

#endif // !SCENE_H




