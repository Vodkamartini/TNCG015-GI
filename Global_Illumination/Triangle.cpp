#include "Triangle.h"

Triangle::Triangle(std::vector<Vertex> vertices, Direction normal, ColorDbl color) : _normal(normal), _color(color) {
	if (vertices.size() != 3)
		printf("\nERROR::Triangle in constructor: Bad vector size: %zi\n", vertices.size());
	else {
		for (unsigned int i = 0; i < vertices.size(); i++) {
			_vertices.push_back(vertices[i]);
		}
		
		assert(_vertices.size() == 3);
	}
}

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, ColorDbl color) : _color(color) {
	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);

	glm::vec3 edge1(_vertices[1] - _vertices[0]);
	glm::vec3 edge2(_vertices[2] - _vertices[0]);

	_normal = glm::normalize(glm::cross(edge1, edge2));
}

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, Direction normal, ColorDbl color) : _normal(normal), _color(color) {
	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);
}

// Based on the Möller-Trumbore algorithm for finding intersections
bool Triangle::rayIntersection(Ray& ray) {
	// Edges of the triangle
	glm::vec3 edge1(_vertices[1] - _vertices[0]);
	glm::vec3 edge2(_vertices[2] - _vertices[0]);

	Direction rayDirection = glm::normalize(ray.getEnd() - ray.getStart());

	glm::vec3 T = glm::vec3(ray.getStart() - _vertices[0]);
	glm::vec3 D = rayDirection;
	glm::vec3 P = glm::cross(D, edge2);
	glm::vec3 Q = glm::cross(T, edge1);

	double paralellCheck = glm::dot(edge1, P);
	if (paralellCheck > -EPSILON && paralellCheck < EPSILON) return NOT_INTERSECTION;	// The ray is parallel to the triangle, no need to continue
		

	float denum = glm::dot(P, edge1);	// Use this to avoid dubplicate code
	
	double u = glm::dot(P, T) / denum;
	if (u >= 1 || u <= 0) return NOT_INTERSECTION;

	double v = glm::dot(Q, D) / denum;
	if (v <= 0.0 ||u + v >= 1.0) return NOT_INTERSECTION;

	double t = glm::dot(Q, edge2) / denum;
	double dist = ray.getClosestIntersection();
	if (t > dist) return NOT_INTERSECTION;

	if (t > EPSILON) {
		ray.updateIntersection(t, ray.getStart() + Vertex(rayDirection, 1.0f) * (float)t, this->getColor(), getNormal());
		return INTERSECTION;
	}
	else {
		return NOT_INTERSECTION;
	}
}

Vertex Triangle::getVertex(unsigned int index) const {
	if (index < _vertices.size())
		return _vertices[index];
	else 
		printf("\nERROR::Triangle in func getVertex: Bad index: %i\n", index);
}

void Triangle::updateVertexPosition(unsigned int index, Vertex newPosition) {
	if (index < _vertices.size()) {
		Vertex newVertex = _vertices[index] + newPosition;
		_vertices[index] = newVertex;
	}
	else
		printf("\nERROR::Triangle in func updateVertexPosition: Bad index: %i\n", index);
}

void Triangle::Print() const {
	printf("\nTriangle vertices:");
	for (unsigned int i = 0; i < _vertices.size(); i++) {
		printf("\nv%i: (%f, %f, %f, %f)", i, _vertices[i].x, _vertices[i].y, _vertices[i].z, _vertices[i].w);
	}
	printf("\nTriangle normal: (%f, %f, %f)", _normal.x, _normal.y, _normal.z);
	printf("\nTriangle color: (%f, %f, %f)\n", (float)_color.r, (float)_color.g, (float)_color.b);
}

const double Triangle::getArea() const {
	return 0.5 * (double)glm::length(glm::cross(glm::vec3(_vertices[1] - _vertices[0]), glm::vec3(_vertices[2] - _vertices[0])));
}

Vertex Triangle::getRandomPoint() const {
	double triangleArea = getArea();
	double a = randMinMax(0.0, 1.0 / triangleArea), b = randMinMax(0.0, 1.0 / triangleArea);
	if (a + b > 1.0) {
		return getRandomPoint();
	}

	return Vertex(fromBarycentric((float)a, (float)b), 1.0f);
}

glm::vec3 Triangle::fromBarycentric(float a, float b) const{
	glm::vec3 pos = (1.0f - a - b) * _vertices[0] + a * _vertices[1] + b * _vertices[2];
	return pos + 0.001f * glm::vec3(0.0f, 0.0f, -1.0f);
}