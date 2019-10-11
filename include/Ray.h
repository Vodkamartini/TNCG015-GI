#ifndef RAY_H
#define RAY_H

#include "Utility.h"

class Triangle;


class Ray {
public:
	Ray() : start(0), end(0), color(0.0) {};
	Vertex getStart();
	Direction getDirection();

private:
	Vertex start;
	Vertex end;
	ColorDbl color;
};

#endif // !RAY_H
