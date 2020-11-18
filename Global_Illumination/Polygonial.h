#ifndef POLYGONIAL_H
#define POLYGONIAL_H
#pragma once
#include "Object.h"
#include "Triangle.h"

class Polygonial : public Object
{
public:
	Polygonial(std::vector<Triangle> triangles, int material, Vertex position);

	const std::vector<Triangle> getTriangles() { return _triangles; };
	bool rayIntersection(Ray& ray) override;

private:
	void positionTriangles(std::vector<Triangle> triangles);

protected:
	std::vector<Triangle> _triangles;
};
#endif // !POLYGONIAL_H


