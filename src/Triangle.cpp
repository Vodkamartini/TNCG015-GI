#include "../include/Triangle.h"

Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Surface& s) {
	positions[0] = v0;
	positions[1] = v1;
	positions[2] = v2;
	surface = s;

	// Set da normale
	normal = glm::normalize(glm::cross(edge1(), edge2()));

}

int Triangle::intersection(Ray& r, Vertex& intersectPoint) {
	Vertex rayStart = r.GetStart();
	Direction direction = glm::normalize(r.GetEnd());
	Vertex pos;

	// Look at intersection function to implement this properly
	glm::vec3 edge1 = this->edge1();
	glm::vec3 edge2 = this->edge2();
	float t1 = 10000000.0f;

	// Calcuate determinant
	Direction edgeNormal = glm::cross(direction, edge2);
	double determinant = glm::dot(edge1, edgeNormal);

	// If determinant is near zero, ray lies in plane of trinagle or ray is parallell to trinagle plane
	if (std::abs(determinant) < DBL_EPSILON)
		return NOT_INTERSECTION;

	double inverted_determinant = 1.0 / determinant;

	// Calculate rayToVertex from first vertex to ray origin
	Vertex rayToVertex = rayStart - positions[0];

	// Calculate u parameter and test bound, if lass than 0 or greater than 1,
	// intersection is outside triangle
	double U = glm::dot(rayToVertex, edgeNormal) * inverted_determinant;
	if (U < 0.f || U > 1.f)
		return NOT_INTERSECTION;

	// Set up Q to be able to calculate V
	Vertex Q = glm::cross(rayToVertex, edge1);
	// Calculate V
	double V = glm::dot(direction, Q) * inverted_determinant;
	//If intersection outside triangle
	if (V < 0.f || V > 1.f)
		return NOT_INTERSECTION;

	double T = glm::dot(edge2, Q) * inverted_determinant;
	if (T > DBL_EPSILON && T < t1) {
		intersectPoint = rayStart + direction * (float)T;
		return INTERSECTION;
	}

	return NOT_INTERSECTION;
}

const Direction& Triangle::getNormal() const {
	return normal;
}
const Surface& Triangle::getSurface() const {
	return surface;
}

Vertex Triangle::getRandomPoint() const{
	double triArea = area();
	double a = randMinMax(0.0, 1.0 / triArea), b = randMinMax(0.0, 1.0 / triArea);
	if (a + b > 1.0) {
		return getRandomPoint();
	}
	return fromBaryCentric((float)a, (float)b);
}

Vertex Triangle::fromBaryCentric(float a, float b) const {
	Vertex pos = (1.0f - a - b) * positions[0] + a * positions[1] + b * positions[2];
	return pos + 0.001f * Vertex(0.0f, 0.0f, -1.0f);
}

double Triangle::area() const {
	return 0.5 * glm::length(glm::cross(edge1(), edge2()));
}

>>>>>>> 60911830b32339a2d5d396603cd73e6953dbf1c1
