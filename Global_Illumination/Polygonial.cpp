#include "Polygonial.h"

Polygonial::Polygonial(std::vector<Triangle> triangles, int material, Vertex position) :
	Object(material, position) {

	positionTriangles(triangles);

}

bool Polygonial::rayIntersection(Ray& ray)  {
	for (Triangle triangle : _triangles) {
		triangle.rayIntersection(ray);
	}

	if (ray.hasIntersection())
		return true;
	else
		return false;
}

void Polygonial::positionTriangles(std::vector<Triangle> triangles) {
	for (int t = 0; t < triangles.size(); t++) {
		Triangle tri = triangles[t];
		for (int v = 0; v < tri.getVertices().size(); v++) {
			tri.updateVertexPosition(v, _position);
		}
		_triangles.push_back(tri);
	}
}