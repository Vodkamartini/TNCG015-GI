#ifndef UTILITY_H
#define UTILITY_H

#include "glm/glm.hpp"

const float EPSILON = 0.00000001f;

using Vertex = glm::vec4;
using Direction = glm::vec3;
using ColorDbl = glm::dvec3;

struct Intersection {

	Intersection() {
		position = Vertex();
		materialType = 1; // LAMBERTIAN by default
		normal = Direction();
		color = ColorDbl();
		distanceToRayOrigin = NULL;
		initialized = false;
	}

	Intersection(Vertex i, ColorDbl c, float dist, int t, Direction n)
		: position(i), color(c), distanceToRayOrigin(dist), materialType(t), normal(n) {
		initialized = true;
	}

	Vertex position;
	Direction normal;
	int materialType;
	ColorDbl color;
	float distanceToRayOrigin;
	bool initialized;
};

#endif // !UTILITY_H
