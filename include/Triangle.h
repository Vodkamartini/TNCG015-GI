#ifdef TRIANGLE_H
#define TRIANGLE_H

#include "glm/glm.hpp"
#include "Utilities.h"

class Triangle {

public:
	Triangle(Vertex& v0, Vertex& v1, Vertex& v2, ColorDb& c1);
	Triangle();

private:
	Vertex v0,v1,v2;
	ColorDb triangle_color;
	Direction normal;

};

#endif // TRIANGLE_H
