#include "../include/Surface.h"

Surface::Surface(const ColorDb& color, const int& model) : color(color), reflectionModel(model) {
	if (model == LIGHTSOURCE)
		emission = ColorDb(20.0);
}

ColorDb Surface::lambertianReflection() const {
	return color * reflectionCoefficient / M_PI;
}

ColorDb Surface::specularReflection() const {
	return color;
}

double Surface::GetReflectionCoefficient() const {
	return reflectionCoefficient;
}

const ColorDb &Surface::getColor() const {
	return HasReflectionModel(SPECULAR ? ColorDb(0.0) : color;
}

const ColorDb& Surface::getEmission() const {
	return emission;
}
