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


	ColorDbl red = ColorDbl(255, 0, 0);
	ColorDbl pink = ColorDbl(255,182,193);
	ColorDbl turquoise = ColorDbl(64,224,208);
	triangles.push_back(Triangle(v0, v1, v2, red));
	triangles.push_back(Triangle(v0, v2, v3, pink));
	triangles.push_back(Triangle(v0, v3, v1, turquoise));
	triangles.push_back(Triangle(v1, v3, v2, red));

}