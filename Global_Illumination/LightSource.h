#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#pragma once

#include "Polygonial.h"
class LightSource : public Polygonial
{
public:
	LightSource(std::vector<Triangle> triangles, int material, Vertex position)
		: Polygonial(triangles, material, position){};

	float GetEmission() const { return emission; }

private: 
	float emission = 400.0f;
};
#endif // LIGHTSOURCE_H



