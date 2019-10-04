#include "../include/Ray.h"

Ray::Ray(Vertex& startPoint, Vertex& endPoint, ColorDb& c) {
	start = startPoint;
	end = endPoint;
	color = c;
}

void Ray::SetDirection(Direction& d) {
	end = d;
}