#include "Ray.h"

Vertex Ray::getStart() {
	return start;
}
Direction Ray::getDirection() {
	return glm::vec3(end - start);
}

ColorDbl Ray::getColor() {
	return color;
}