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
	void setColor(ColorDbl c);
	Direction getDirection() const;
	//Direction getNormal() const { return objectNormal; }
	//void setObjectNormal(Direction dir) { objectNormal = dir; }
	double getClosestIntersection() const;
	void setClosestIntersection(double tnew);
	bool hasIntersection() { return intersection.initialized; };
	Intersection getIntersection() { return intersection; };
	void setIntersection(Intersection i);
private:
	Vertex start;
	Vertex end;
	double t = 10000;
	ColorDbl color;
	Intersection intersection;
	//Direction objectNormal;
};

#endif // !RAY_H
