#include "Triangle.h"


bool Triangle::rayIntersection(Ray& r) {
	
	// Negative because of camera oriented along the negative z-axis
	if (glm::dot(normal, r.getDirection()) == 0) {
		return NOT_INTERSECTION; // Triangle and ray are parallel
	}
	
	float t = -(glm::dot(normal, glm::vec3(r.getStart())) + d) / glm::dot(normal, r.getDirection());	
	
	if (t < 0) {
		return NOT_INTERSECTION; // Behind the rays origin
	}

	Vertex p = (r.getStart() + t) * glm::vec4(r.getDirection(), 0);
	//Inside outside test
	Vertex c0 = p - v0;
	Vertex c1 = p - v1;
	Vertex c2 = p - v2;
	if (glm::dot(normal, glm::cross(edge0(), glm::vec3(c0))) > 0 &&
		glm::dot(normal, glm::cross(edge1(), glm::vec3(c1))) > 0 &&
		glm::dot(normal, glm::cross(edge2(), glm::vec3(c2))) > 0) 
	{
		return INTERSECTION;
	}
}

double Triangle::area() const {
	return 0.5 * glm::length(glm::cross(edge1(), edge2()));
}

float Triangle::getPlaneParam() const {
	return glm::dot(normal, glm::vec3(v0)); // The D-term in the triangle's plane equation (relativity to origin)
}