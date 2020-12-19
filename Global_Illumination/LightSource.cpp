#include "LightSource.h"

LightSource::LightSource(std::vector<Triangle> triangles, int material, Vertex position, double emission) :
	Object(material, position), _emission(emission) {

	positionTriangles(triangles);
}

bool LightSource::rayIntersection(Ray& ray)  {
	for (Triangle triangle : _triangles) {
		triangle.rayIntersection(ray);
	}

	if (ray.hasIntersection())
		return true;
	else
		return false;
}

void LightSource::positionTriangles(std::vector<Triangle>& triangles) {
	for (int t = 0; t < triangles.size(); t++) {
		Triangle tri = triangles[t];
		for (int v = 0; v < tri.getVertices().size(); v++) {
			tri.updateVertexPosition(v, _position);
		}
		_triangles.push_back(tri);
	}
}