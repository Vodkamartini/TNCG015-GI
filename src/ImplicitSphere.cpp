#include "ImplicitSphere.h"

bool ImplicitSphere::rayIntersection(Ray& r) {
	float a = 1.f; //Dot product of the ray direction with itself is always 1.
	glm::vec3 L = r.getStart() - center;
	float b = glm::dot(2.0f * r.getDirection(), L);
	float c = glm::dot(L, L) - radiusSquared;
	
	float d0, d1;
	if (!stableQuadraticSolver(a, b, c, d0, d1)) return false;

	//If d0 is further away then d1 swaps position with it
	if (d0 > d1) std::swap(d0, d1);

	//Tangent case
	if (d0 < 0) {
		d0 = d1;
			if (d0 < 0) return false;
	}
	
	if (abs(d0) < EPSILON)
		return false;

	if (!r.hasIntersection() || r.getIntersection().distanceToRayOrigin > d0) {
		Vertex intersectionPoint = Vertex(r.getStart() + glm::vec4(d0 * r.getDirection(), 1.0f));
		r.setIntersection(Intersection(intersectionPoint, material.getColor(), d0, material.getType(), glm::normalize(glm::vec3(intersectionPoint - center))));
	}

	return true;
}

bool ImplicitSphere::stableQuadraticSolver(const float& a, const float& b, const float& c, float& x0, float& x1) 
{
	//Return false if there are no real solutions to intersection!
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) return false;
	else if (glm::abs(discriminant) < EPSILON) x0 = x1 = -0.5f * b / a;
	else {
		float q = (b > 0) ?
			-0.5f * (b + sqrt(discriminant)) :
			-0.5f * (b - sqrt(discriminant));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}