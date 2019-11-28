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
		color = ColorDbl();
		distanceToRayOrigin = NULL;
		initialized = false;
	}

	Intersection(Vertex i, ColorDbl c, float dist)
		: position(i), color(c), distanceToRayOrigin(dist) {
		initialized = true;
	}

	Vertex position;
	ColorDbl color;
	float distanceToRayOrigin;
	bool initialized;
};

#endif // !UTILITY_H
