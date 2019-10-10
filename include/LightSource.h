#ifndef LIGHTSOURCE_H_INCLUDED
#define LIGHTSOURCE_H_INCLUDED

#include "glm/glm.hpp"
#include "Utilities.h"
#include <vector>
#include "Triangle.h"

class LightSource {
public:
	LightSource();
	const std::vector<Triangle>& getTriangles() const;
private:
	std::vector<Triangle> triangles;
};

#endif // !LIGHTSOURCE_H_INCLUDED
