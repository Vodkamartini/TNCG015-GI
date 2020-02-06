#include "Tetrahedron.h"


Tetrahedron::Tetrahedron() {
	color = ColorDbl(255, 0, 0);
	createTriangles();
}

Tetrahedron::Tetrahedron(Vertex pos, ColorDbl color) {
	color = color;
	position = pos;
	createTriangles();
}


void Tetrahedron::createTriangles() {
	v0 = v0 + position;
	v1 = v1 + position;
	v2 = v2 + position;
	v3 = v3 + position;


	const ColorDbl Red = ColorDbl(255, 0, 0);
	const ColorDbl Pink = ColorDbl(255,182,193);
	const ColorDbl Turquoise = ColorDbl(64,224,208);

	const Material RedMaterial = Material(Red, LAMBERTIAN, glm::vec3(0.f), 1.0f);
	const Material PinkMaterial = Material(Pink, LAMBERTIAN, glm::vec3(0.f), 1.0f);
	const Material TurquoiseMaterial = Material(Turquoise, LAMBERTIAN, glm::vec3(0.f), 1.0f);

	triangles.push_back(Triangle(v0, v1, v2, RedMaterial));
	triangles.push_back(Triangle(v0, v2, v3, PinkMaterial));
	triangles.push_back(Triangle(v0, v3, v1, TurquoiseMaterial));
	triangles.push_back(Triangle(v1, v3, v2, RedMaterial));

}