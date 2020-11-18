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
		ray.updateIntersection(d0, intersectionPoint, this->getColor());
		return INTERSECTION;
	}
}

