#include "Triangle.h"
#include <iostream>


bool Triangle::rayIntersection(Ray& r) {
	
	glm::vec4 T = r.getStart() - v0;
	glm::vec3 D = r.getDirection();
	glm::vec4 P = glm::vec4(glm::cross(D,edge1()),1.0f);
	glm::vec4 Q = glm::vec4(glm::cross(glm::vec3(T), edge0()), 1.0f);

	double t = glm::dot(glm::vec3(Q), edge1()) / glm::dot(glm::vec3(P), edge0());
	double u = glm::dot(glm::vec3(P), glm::vec3(T)) / glm::dot(glm::vec3(P), edge0());
	double v = glm::dot(glm::vec3(Q), D) / glm::dot(glm::vec3(P), edge0());

	if (t > r.getClosestIntersection()) return NOT_INTERSECTION;

	if ((t > EPSILON) && (u <= 1) && (u >= 0) && (v <= 1) && (v >= 0) && (u + v <= 1))
	{
		r.setClosestIntersection(t);
		//r.setObjectNormal(normal);
		//r.setIntersection(v0 + glm::vec4( edge0()*(float)u + edge1()*(float)v + normal * 0.01f, 1.0f));
		if (!r.hasIntersection() || r.getIntersection().distanceToRayOrigin > t) {
			r.setIntersection(Intersection(r.getStart() + glm::vec4((float)t * r.getDirection(), 1.0), r.getColor(), t));
			return INTERSECTION;
		}
	}

	return NOT_INTERSECTION;
}

double Triangle::area() const {
	return 0.5 * glm::length(glm::cross(edge0(), edge1()));
}

float Triangle::getPlaneParam() const {
	return glm::dot(normal, glm::vec3(v0)); // The D-term in the triangle's plane equation (relativity to origin)
}