#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include <glm/glm.hpp>
#include "Surface.h"

const int INTERSECTION = 1;
const int NOT_INTERSECTION = 0;


class Triangle {

public:
	Triangle() : Triangle(Vertex(), Vertex(), Vertex()) {};
	Triangle(const Vertex& v0,const Vertex& v1,const Vertex& v2,const Surface& s = Surface());
	
	int intersection(Ray&, Vertex&);
	Direction calcNormal() { return glm::normalize(glm::cross(edge1(), edge2())); }
	
	const Direction& getNormal() const;
	const Surface& getSurface() const;

	Vertex getRandomPoint() const;
	Vertex fromBaryCentric(float a, float b) const;
	double area() const;

private:
	std::array<Vertex, 3> positions;
	Surface surface;
	Direction normal;
	glm::vec3 edge1() const { return positions[1] - positions[0]; }
	glm::vec3 edge2() const { return positions[2] - positions[0]; }
};

#endif // TRIANGLE_H
