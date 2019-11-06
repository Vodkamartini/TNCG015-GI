#include "Triangle.h"
#include <iostream>


bool Triangle::rayIntersection(Ray& r, Vertex& intersection) {
	
	// Calculate p and detarminant
	/*Direction pvec = glm::cross(edge1(), r.getDirection());
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
	
	if (t > EPSILON) {
		intersection = glm::vec4(glm::vec3(r.getStart()) + r.getDirection() * t, 0);	// update the intersection point
		return INTERSECTION; // We made it all the way through --> Intersection!
	}
	return NOT_INTERSECTION; */
	glm::vec4 T = r.getStart() - v0;
	glm::vec4 E1 = v1 - v0;
	glm::vec4 E2 = v2 - v0;
	glm::vec4 D = r.getEnd() - r.getStart();
	glm::vec4 P = glm::vec4(glm::cross(glm::vec3(D),glm::vec3(E2)),1.0f);
	glm::vec4 Q = glm::vec4(glm::cross(glm::vec3(T), glm::vec3(E1)), 1.0f);;

	double t = glm::dot(glm::vec3(Q), glm::vec3(E2)) / glm::dot(glm::vec3(P), glm::vec3(E1));
	double u = glm::dot(glm::vec3(P), glm::vec3(T)) / glm::dot(glm::vec3(P), glm::vec3(E1));
	double v = glm::dot(glm::vec3(Q), glm::vec3(D)) / glm::dot(glm::vec3(P), glm::vec3(E1));

	//if (t > r.t) return false;

	if ((t > 0) && (u <= 1) && (u >= 0) && (v <= 1) && (v >= 0) && (u + v <= 1))
	{
		//ray.t = t;
		//r.objectNormal = normal;
		//ray.intersection = a + E1 * u + E2 * v + normal * 0.01;
		return true;
	}

	return false;
}

double Triangle::area() const {
	return 0.5 * glm::length(glm::cross(edge0(), edge1()));
}

float Triangle::getPlaneParam() const {
	return glm::dot(normal, glm::vec3(v0)); // The D-term in the triangle's plane equation (relativity to origin)
}