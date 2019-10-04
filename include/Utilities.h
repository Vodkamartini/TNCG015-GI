#pragma once

#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <glm/glm.hpp>	// vec2, vec3, mat4, radians
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <iostream>

using Vertex = glm::vec4;				// Three coordinates: x,y,z and one homogeneous: w
using Direction = glm::vec3;			// Three coordinate direction
using ColorDb = glm::dvec3;				// Double precision color vector
using ColorInt = std::array<int, 3>;	// Integer precision color vector

#endif // !UTILITIES_H_INCLUDED