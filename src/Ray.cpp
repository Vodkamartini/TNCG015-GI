#include "Ray.h"

Vertex Ray::getStart() {
	return start;
}
Vertex Ray::getEnd() {
	return end;
}
Direction Ray::getDirection() {
	return glm::vec3(end - start);
}

ColorDbl Ray::getColor() {
	return color;
}