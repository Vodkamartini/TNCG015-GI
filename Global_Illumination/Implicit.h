#ifndef IMPLICIT_H
#define IMPLICIT_H
#pragma once
#include "Object.h"

class Implicit : public Object
{
public:
	Implicit(ColorDbl color, int material, Vertex position) :
		_color(color), Object(material, position) {};

	const ColorDbl getColor() { return _color; };

	bool rayIntersection(Ray& ray) override;
	bool stableQuadraticSolver(const float& a, const float& b, const float& c, float& x0, float& x1);

protected:
	ColorDbl _color;
};
#endif // !IMPLICIT_H



