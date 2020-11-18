#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "utils.h"
#include "Triangle.h"
#include "Polygonial.h"
#include "LightSource.h"
#include "Sphere.h"
class Scene
{
public:
	Scene();

	bool detectIntersection(Ray& ray);
	void addPolygonial(Polygonial object);
	void addImplicit(Sphere object);
	void addLightsource(LightSource object);
private:
	void createRoom();

	std::vector<Triangle> _triangles;
	std::vector<Vertex> _vertices;
	std::vector<Polygonial> _polys;
	std::vector<Sphere> _implicits;
	std::vector<LightSource> _lightSources;
};

#endif // !SCENE_H




