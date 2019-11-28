#ifndef RAY_H
#define RAY_H

#include "Utility.h"

class Triangle;


class Ray {
public:
	Ray() : start(0), end(0), color(0.0) {};
	Ray(Vertex start, Vertex end) : start(start), end(end) { color = ColorDbl(0); };
	~Ray() {};
	Vertex getStart() const;
	Vertex getEnd() const;
	ColorDbl getColor() const;
	Direction getDirection() const;
	//Direction getNormal() const { return objectNormal; }
	//void setObjectNormal(Direction dir) { objectNormal = dir; }
	double getClosestIntersection() const;
	void setClosestIntersection(double tnew);
	//void setIntersection(Vertex i);
private:
	Vertex start;
	Vertex end;
	double t = 10000;
	ColorDbl color;
	//Vertex intersection;
	//Direction objectNormal;
};

#endif // !RAY_H
