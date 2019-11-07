#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "Utility.h"
#include "Triangle.h"
#include <vector>
#include <iostream>

class Tetrahedron {
public:
	Tetrahedron();

	Tetrahedron(Vertex pos, ColorDbl color);

	void createTriangles();

	std::vector<Triangle> getTriangles() const{
		return triangles;
	}

private:
	Vertex v0 = Vertex(1.0f, 1.0f, 1.0f, 1.0f); 
	Vertex v1 = Vertex(1.0f, -1.0f, -1.0f, 1.0f);
	Vertex v2 = Vertex(-1.0f, 1.0f, -1.0f, 1.0f);
	Vertex v3 = Vertex(-1.0f, -1.0f, -1.0f, 1.0f);
	ColorDbl color;
	std::vector<Triangle> triangles;
	Vertex position = Vertex(8.0f, 3.0f, -4.0f, 0.0f);
};



#endif // !TETRAHEDRON_H