#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#pragma once

#include "Object.h"
#include "Triangle.h"
class LightSource : public Object
{
public:
	LightSource(std::vector<Triangle> triangles, int material, Vertex position, double emission);
		
	const double getEmission() const { return _emission; }
	const std::vector<Triangle> getTriangles() { return _triangles; };
	bool rayIntersection(Ray& ray) override;

private: 
	void positionTriangles(std::vector<Triangle>& triangles);

	double _emission;
	std::vector<Triangle> _triangles;
};
#endif // LIGHTSOURCE_H



