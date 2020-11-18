#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once

#include "utils.h"
#include "Ray.h"

const bool INTERSECTION = true;
const bool NOT_INTERSECTION = false;

class Ray;

class Triangle
{

public:
	Triangle(std::vector<Vertex> vertices, Direction normal, ColorDbl color);
	Triangle(Vertex v1, Vertex v2, Vertex v3, ColorDbl color);
	Triangle(Vertex v1, Vertex v2, Vertex v3, Direction normal, ColorDbl color);

	bool rayIntersection(Ray& arg);

	std::vector<Vertex> getVertices() const { return _vertices; };
	Vertex getVertex(unsigned int index) const;
	Direction getNormal() const { return _normal; };
	ColorDbl getColor() const { return _color; };

	void updateVertexPosition(unsigned int index, Vertex newPosition);

	void Print() const;
private:
	
	std::vector<Vertex> _vertices;
	Direction _normal;
	ColorDbl _color;
};

#endif // !TRIANGLE_H