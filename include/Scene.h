#ifndef SCENE_H
#define SCENE_H

#include <array>
#include <vector>
#include <list>
#include <glm/gtx/vector_angle.hpp>
#include "Triangle.h"
#include "Ray.h"
#include "LightSource.h"

struct TriangleIntersection {
	Triangle triangle;
	Vertex point;
};

const int SHADOW_RAY_COUNT = 2;


static const float INTERSECTION_MARGIN = 0.001f;

class Scene {
public:
	Scene();
	void createRoom();
	std::list<TriangleIntersection> detectIntersections(Ray ray) const;
	void importTriangles(std::vector<Triangle> triangles);
	void importTriangle(Triangle& t);
	void importLightSources(std::vector<LightSource> lightsources);
	void importLightSource(LightSource& l);

	ColorDb getLightContribution(const Vertex& point, const Direction& normal) const;

private:
	std::vector<Triangle> triangles;
	std::vector<LightSource> lightsources;
};
#endif // SCENE_H
