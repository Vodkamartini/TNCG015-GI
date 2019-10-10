#include "LightSource.h"

LightSource::LightSource() {
	glm::dvec3 a(-1.0, 4.99, 8.0);
	glm::dvec3 b(1.0, 4.99, 8.0);
	glm::dvec3 c(-1.0, 4.99, 6.0);
	glm::dvec3 d(1.0, 4.99, 6.0);

	const Surface white(ColorDb(1.0f), LIGHTSOURCE);
	triangles.push_back(Triangle(a, d, b, white));
	triangles.push_back(Triangle(a, c, d, white));
}

const std::vector<Triangle>& LightSource::getTriangles() const{
	return triangles;
}