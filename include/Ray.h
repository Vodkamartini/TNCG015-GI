#ifndef RAY_H
#define RAY_H

#include "Utilities.h"
#include <glm/gtx/rotate_vector.hpp>


class Ray {

public:
	// Ray is defined by a start point, an end point and a color
	Ray() : start(0.0), end(0.0), color(0.0), direction(0.0) {};
	Ray(Direction start, Direction end);
	Ray(Vertex& startPoint, Vertex& endPoint, ColorDb& c);
	~Ray() {};
	Ray bounce(const Vertex& position, const Direction& normal) const;
	// Get functions
	Vertex GetStart() { return start; }
	Vertex GetEnd() { return end; }
	ColorDb GetColor() { return color; }

	// Set functions
	void SetDirection(Direction& d);
	void SetColor(ColorDb c) { color = c; }
	Ray sampleHemisphere(const Vertex& position, const Direction normal) const;

private:
	Vertex start;
	Vertex end;
	Direction direction;
	ColorDb color;
};

#endif // RAY_H
