#include "../include/Ray.h"

Ray::Ray(Vertex& startPoint, Vertex& endPoint, ColorDb& c) {
	start = startPoint;
	end = endPoint;
	color = c;
	direction = end - start;
}

Ray::Ray(Direction start, Direction end) {
	start = start;
	end = end;
}

Ray Ray::bounce(const Vertex& position, const Direction& normal) const {
	Direction newDirection = glm::reflect(direction, normal);
	Ray r(position, newDirection);
	return r;
}

void Ray::SetDirection(Direction& d) {
	Ray::direction = d;
}
Ray Ray::sampleHemisphere(const Vertex& position, const Direction normal) const {
	float rand1 = uniformRand();
	float rand2 = uniformRand();

	Direction helper = normal + Direction(1, 1, 1);
	Direction tangent = glm::normalize(glm::cross(normal, helper));
	float inclination = acos(sqrt(rand1));
	float azimuth = 2 * M_PI * rand2;
	// Change the actual vector
	Direction random_direction = normal;
	random_direction = glm::normalize(glm::rotate(
		random_direction,
		inclination,
		tangent));
	random_direction = glm::normalize(glm::rotate(
		random_direction,
		azimuth,
		normal));

	return Ray(position, random_direction);
}

