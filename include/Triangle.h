#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Utility.h"
#include "Ray.h"
#include "Material.h"

const bool INTERSECTION = true;
const bool NOT_INTERSECTION = false;

class Triangle {
public:
	Triangle() : v0(0), v1(0), v2(0), material(Material()) {
		normal = glm::cross(edge0(), edge1());
		d = getPlaneParam();
	};

	Triangle(Vertex v0, Vertex v1, Vertex v2, Material m) : v0(v0), v1(v1), v2(v2), material(m) {
		normal = glm::cross(edge0(), edge1());
		d = getPlaneParam();
	};

	bool rayIntersection(Ray& r);
	double area() const;
	float getPlaneParam() const;
	ColorDbl getColor() {
		return material.getColor();
	}

private:
	Vertex v0, v1, v2;
	//ColorDbl color;
	Material material;
	Direction normal;
	Direction edge0() const { return v1 - v0; };
	Direction edge1() const { return v2 - v0; };
	float d;
};

#endif // !TRIANGLE_H