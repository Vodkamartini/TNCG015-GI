#ifndef MATERIAL_H
#define MATERIAL_H

#include "Utility.h"

const int LAMBERTIAN = 0;
const int PERFECT_REFLECTOR = 1;
const int LIGHT = 2;	// Lightsource

const float one_over_pi = 0.31830988618379f;

class Material {
public:
	Material() : color(ColorDbl()), type(LAMBERTIAN), rho(glm::vec3(0.f)), alpha(1.0f) {
		normalizationFactor = one_over_pi * rho;
	};
	Material(ColorDbl colorIn, int typeIn, glm::vec3 rhoIn, float alphaIn) : color(colorIn), type(typeIn), rho(rhoIn), alpha(alphaIn) {
		normalizationFactor = one_over_pi * rho;
	};
	ColorDbl getColor() { return color; }
	int getType() { return type; }

	Direction BRDF();

private:
	int type;
	ColorDbl color;
	glm::vec3 rho;
	glm::vec3 normalizationFactor;
	float alpha;
};
#endif	// !MATERIAL_H