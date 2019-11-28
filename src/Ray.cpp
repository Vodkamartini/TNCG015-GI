#include "Ray.h"

Vertex Ray::getStart() const {
	return start;
}
Vertex Ray::getEnd() const {
	return end;
}
Direction Ray::getDirection() const {
	return glm::vec3(end - start);
}

double Ray::getClosestIntersection() const {
	return t;
}

void Ray::setClosestIntersection(double tnew) {
	t = tnew;
}

ColorDbl Ray::getColor() const {
	return color;
}

void Ray::setIntersection(Intersection i) {
	intersection = Intersection(i.position, i.color, i.distanceToRayOrigin);
}