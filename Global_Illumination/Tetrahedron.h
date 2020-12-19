#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H
#pragma once
#include "Object.h"
#include "Triangle.h"

class Tetrahedron : public Object
{
public:
	Tetrahedron(std::vector<Triangle> triangles, int material, Vertex position);

	const std::vector<Triangle> getTriangles() { return _triangles; };
	bool rayIntersection(Ray& ray) override;

private:
	void positionTriangles(std::vector<Triangle>& triangles);

	std::vector<Triangle> _triangles;
};

#endif // !TETRAHEDRON_H




