#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#pragma once

#include "Polygonial.h"
class LightSource : public Polygonial
{
public:
	LightSource()
	{
		Vertex v0(-1.0f, 4.99f, 8.0f, 1.0f);
		Vertex v1(1.0f, 4.99f, 8.0f, 1.0f);
		Vertex v2(-1.0f, 4.99f, 6.0f, 1.0f);
		Vertex v3(1.0f, 4.99f, 6.0f, 1.0f);

		_triangles = { (Triangle(v0, v3, v1, ColorDbl(255, 0, 255))), (Triangle(v0, v2, v3, ColorDbl(255, 0, 255))) };
		Polygonial(std::vector<Triangle>(), 2, Vertex(0.0f));
	}
};
#endif // !LIGHTSOURCE_H



