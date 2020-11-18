#include "utils.h"
#include "Camera.h"
#include "Scene.h"
#include "Tetrahedron.h"
#include "Sphere.h"
#include "LightSource.h"

int main() {

	// Tetrahedron
	Vertex v0(1.0f, 1.0f, 1.0f, 1.0f);
	Vertex v1(1.0f, -1.0f, -1.0f, 1.0f);
	Vertex v2(-1.0f, 1.0f, -1.0f, 1.0f);
	Vertex v3(-1.0f, -1.0f, -1.0f, 1.0f);
	
	Triangle t0(v0, v1, v2, ColorDbl(255, 0, 0));
	Triangle t1(v0, v2, v3, ColorDbl(255, 182, 193));
	Triangle t2(v0, v3, v1, ColorDbl(64, 224, 208));
	Triangle t3(v1, v3, v2, ColorDbl(0, 255, 0));

	std::vector<Triangle> tetrahedronTriangles = { t0, t1, t2, t3 };
	Tetrahedron tetrahedron(tetrahedronTriangles, 0, Vertex(8.0f, 3.0f, -4.0f, 1.0f));

	// Sphere
	Sphere sphere(Vertex(5.0f, -3.0f, 2.0f, 1.0f), 1.0f, ColorDbl(255, 211, 0), 2, Vertex(5.0f, -3.0f, 2.0f, 1.0f));

	Vertex eye1(-2.0f, 0.0f, 0.0f, 1.0f);
	Vertex eye2(-1.0f, 0.0f, 0.0f, 1.0f);

	Camera cam(eye1, eye2, 800, 800);
	Scene scene;

	scene.addPolygonial(tetrahedron);
	scene.addImplicit(sphere);
	scene.addLightsource(LightSource());	// Add default lightsource to scene
	cam.switchEye();
	cam.render(&scene);
}