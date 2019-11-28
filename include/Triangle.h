#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Utility.h"
#include "Ray.h"

const bool INTERSECTION = true;
const bool NOT_INTERSECTION = false;

class Triangle {
public:
	Triangle() : v0(0), v1(0), v2(0), color(0.0) {
		normal = glm::cross(edge0(), edge1());
		d = getPlaneParam();
	};

	Triangle(Vertex v0, Vertex v1, Vertex v2, ColorDbl c) : v0(v0), v1(v1), v2(v2), color(c) {
		normal = glm::cross(edge0(), edge1());
		d = getPlaneParam();
	};

	bool rayIntersection(Ray& r);
	double area() const;
	float getPlaneParam() const;
	ColorDbl getColor() {
		return color;
	}

private:
	Vertex v0, v1, v2;
	ColorDbl color;
	Direction normal;
	Direction edge0() const { return v1 - v0; };
	Direction edge1() const { return v2 - v0; };
	//Direction edge2() const { return v0 - v2; };
	float d;
};

#endif // !TRIANGLE_H