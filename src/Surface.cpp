#include "Surface.h"

Surface::Surface(const ColorDb& color, const int& model) : color(color), reflectionModel(model) {
	if (model == LIGHTSOURCE)
		emission = ColorDb(20.0);
}

ColorDb Surface::reflect(const Ray& in, const Ray& out, const Direction& normal) const {
	switch (reflectionModel) {
	case LAMBERTIAN:
		return lambertianReflection();
	case SPECULAR:
		return specularReflection();
	default:
		std::cout << "INVALID REFLECTION MODEL: " << reflectionModel << std::endl;
		return ColorDb(0.0);
	}
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

Ray Surface::bounceRay(const Ray& in, const Vertex &position, const Direction& normal) const {
	switch (reflectionModel) {
	case LAMBERTIAN:
		return in.sampleHemisphere(position, normal);
	case SPECULAR:
		return in.bounce(position, normal);
	default:
		std::cout << "INVALID REFLECTION MODEL: " << reflectionModel << std::endl;
		Ray r;
		return r;
	}
}

const ColorDb& Surface::GetColor() const {
	return HasReflectionModel(SPECULAR) ? ColorDb(0.0) : color;
}

const ColorDb& Surface::GetEmission() const {
	return emission;
}
