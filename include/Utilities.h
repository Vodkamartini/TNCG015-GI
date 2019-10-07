#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#define _USE_MATH_DEFINES
#include <glm/glm.hpp>	// vec2, vec3, mat4, radians
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <iostream>
#include <random>

using Vertex = glm::vec3;				// Three coordinates: x,y,z and one homogeneous: w
using Direction = glm::vec3;			// Three coordinate direction
using ColorDb = glm::dvec3;				// Double precision color vector
using ColorInt = std::array<int, 3>;	// Integer precision color vector
static std::uniform_real_distribution<double> DISTR(0.0, 1.0);
static std::default_random_engine GENERATOR;

double uniformRand();

double randMinMax(const double& min, const double& max);
#endif // !UTILITIES_H_INCLUDED