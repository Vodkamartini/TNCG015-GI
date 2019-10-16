#include "Triangle.h"


bool Triangle::rayIntersection(Ray& r, Vertex& intersection) {
	
	// Calculate p and detarminant
	Direction pvec = glm::cross(edge1(), r.getDirection());
	float det = glm::dot(edge0(), pvec);

	if (det < EPSILON) {
		return NOT_INTERSECTION; // Triangle and ray are parallel --> No intersection
	}
	
	float invDet = 1 / det;

	Direction tvec = glm::vec3(r.getStart() - v0);
	float u = (glm::dot(tvec, pvec)) * invDet;
	if (u < 0 || u > 1)
	{
		return NOT_INTERSECTION; // u is out of bounds --> No intersection
	}

	Direction qvec = glm::cross(tvec, edge0());
	float v = (glm::dot(glm::vec3(r.getDirection()), qvec)) * invDet;
	if (v < 0 || u + v > 1)
	{
		return NOT_INTERSECTION; // v is out of bounds --> No intersection
	}

	
	float t = (glm::dot(edge1(), qvec)) * invDet;	// t represents the distance from the ray's origin to the intersection point P
	intersection = glm::vec4(glm::vec3(r.getStart()) + r.getDirection() * t, 0);	// update the intersection point
	return INTERSECTION; // We made it all the way through --> Intersection!
}

double Triangle::area() const {
	return 0.5 * glm::length(glm::cross(edge0(), edge1()));
}

float Triangle::getPlaneParam() const {
	return glm::dot(normal, glm::vec3(v0)); // The D-term in the triangle's plane equation (relativity to origin)
}