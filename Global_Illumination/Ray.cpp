#include "Ray.h"

Ray::Ray(std::vector<Vertex> vertices) {
	if (vertices.size() != 2)
		printf("\nERROR::Ray in constructor: Bad vector size: %i\n", vertices.size());
	else {
		for (unsigned int i = 0; i < vertices.size(); i++) {
			_vertices.push_back(vertices[i]);
		}

		assert(_vertices.size() == 2);
	}
}

Ray::Ray(Vertex start, Vertex end) {
	_vertices.push_back(start);
	_vertices.push_back(end);
}

// Update intersection data and set ray color to match triangle color
void Ray::updateIntersection(double distance, Vertex position, ColorDbl color) {
	//_intersection._intersectedTriangle = triangle;
	_intersection._color = color;
	_intersection._distance = distance;
	_intersection._position = position;
	_intersection._hasIntersection = true;
}

void Ray::Print() const {
	printf("\nRay vertices:");
	for (unsigned int i = 0; i < _vertices.size(); i++) {
		printf("\nv%i: (%f, %f, %f, %f)", i, _vertices[i].x, _vertices[i].y, _vertices[i].z, _vertices[i].w);
	}
	printf("\nRay color: (%f, %f, %f)\n", (float)_intersection._color.r, (float)_intersection._color.g, (float)_intersection._color.b);
}

void Ray::PrintIntersection() const {
	if (_intersection._hasIntersection) {
		printf("\n----------------------\nRay Intersection:");
		//printf("\nIntersected triangle:");
		//_intersection._intersectedTriangle->Print();

		printf("\nIntersection distance: %f", (float)_intersection._distance);
		printf("\nIntersection position: (%f, %f, %f)\n", _intersection._position.x, _intersection._position.y, _intersection._position.z);
		printf("----------------------\n");
	}
	else {
		printf("\nNo intersection! \n");
	}
}
