#ifdef RAY_H
#define RAY_H

#include "Utilities.h"

class Ray {

public:
	// Ray is defined by a start point, an end point and a color
	Ray(Vertex& startPoint, Vertex& endPoint, ColorDb& c);

	// Get functions
	Vertex GetStart() { return start };
	Vertex GetEnd() { return end };
	ColorDb GetColor() { return color };

	// Set functions
	void SetDirection(Direction& d);
	void SetColor(ColorDb c) { color = c; }


private:
	Vertex start;
	Vertex end;
	ColorDb color;
};

#endif // RAY_H
