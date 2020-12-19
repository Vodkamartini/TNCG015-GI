#include "Sphere.h"

bool Sphere::rayIntersection(Ray& ray)	{
	Direction rayDirection = glm::normalize(ray.getEnd() - ray.getStart());
	glm::vec3 L = glm::vec3(ray.getStart() - _center);

	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot(rayDirection, L);
	float c = glm::dot(L, L) - (_radius * _radius);

	// function stableQuadraticSolver will alter d0 and d1
	float d0, d1;
		if (!stableQuadraticSolver(a, b, c, d0, d1)) {
 		return NOT_INTERSECTION;
	}
	
	if (d0 > d1) {
		std::swap(d0, d1);
	}

	// Tanget case
	if (d0 < 0) {
		d0 = d1;
		if (d0 < 0) {
			return NOT_INTERSECTION;
		}
	}

	if (abs(d0) < EPSILON) {
		return NOT_INTERSECTION;
	}

	if (!ray.hasIntersection() || ray.getClosestIntersection() > d0) {
		Vertex intersectionPoint = Vertex(ray.getStart() + glm::vec4(rayDirection * d0, 1.0f));
		ray.updateIntersection(d0, intersectionPoint, this->getColor(), (Direction)glm::normalize(intersectionPoint - _center));
		return INTERSECTION;
	}
}

// Analytic stable quadratic solver from: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
bool Sphere::stableQuadraticSolver(const float& a, const float& b, const float& c, float& x0, float& x1)
{
	// Return false if there are no real solutions
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) return false;
	else if (discriminant == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discriminant)) :
			-0.5 * (b - sqrt(discriminant));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}