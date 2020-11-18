#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H
#pragma once
#include "Polygonial.h"

class Tetrahedron : public Polygonial
{
public:
	Tetrahedron(std::vector<Triangle> triangles, int material, Vertex position) :
		Polygonial(triangles, material, position) {};
};

#endif // !TETRAHEDRON_H




