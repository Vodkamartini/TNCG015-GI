#ifndef RAY_H
#define RAY_H

#pragma once

#include "utils.h"
#include "Triangle.h"

class Triangle;

class Ray
{
public:

	Ray(std::vector<Vertex> vertices);
	Ray(Vertex start, Vertex end);

	Vertex getStart() const { return _vertices[0]; };
	Vertex getEnd() const { return _vertices[1]; };
	ColorDbl getColor() const { return hasIntersection() ? _intersection._color : ColorDbl(-1, -1, -1); };
	double getClosestIntersection() const { return _intersection._distance; };
	bool hasIntersection() const { return _intersection._hasIntersection; };

	void updateIntersection(double distance, Vertex position, ColorDbl color, Direction normal, int material);
	const Vertex& getIntersectionPoint() const { return _intersection._position; };
	const Direction& getIntersectionNormal() const { return _intersection._normal; };
	const int getIntersectionMaterial() const { return _intersection._material; };

	void Print() const;
	void PrintIntersection() const;

private:

	std::vector<Vertex> _vertices;
	
	struct Intersection {
		//Triangle* _intersectedTriangle;
		ColorDbl _color;
		Direction _normal;
		double _distance = 10000.0;
		Vertex _position = Vertex(10000.0, 10000.0, 10000.0, 10000.0);
		bool _hasIntersection = false;
		int _material = -1;
	};

	Intersection _intersection;
};

#endif //RAY_H