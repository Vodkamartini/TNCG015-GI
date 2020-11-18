#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include "utils.h"
#include "Ray.h"
class Object
{
public:
	Object(int material, Vertex position) : 
		_material(material), _position(position) {};

	const int getMaterial() { return _material; };
	const Vertex getPosition() { return _position; };
	virtual bool rayIntersection(Ray& ray);	// Should always be overridden by children

protected:
	int _material;
	Vertex _position;

};
#endif // OBJECT_H
	