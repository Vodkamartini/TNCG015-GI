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
	
	Triangle t0(v0, v1, v2, RED);
	Triangle t1(v0, v2, v3, RED);
	Triangle t2(v0, v3, v1, RED);
	Triangle t3(v1, v3, v2, RED);

	std::vector<Triangle> tetrahedronTriangles = { t0, t1, t2, t3 };
	Tetrahedron* tetrahedron = new Tetrahedron(tetrahedronTriangles, 1, Vertex(6.0f, 2.5f, -4.0f, 1.0f));

	// Sphere
	Sphere* sphere = new Sphere(Vertex(5.0f, -3.0f, 1.0f, 1.0f), 1.5f, ColorDbl(255, 211, 0), 1, Vertex(5.0f, -3.0f, 1.0f, 1.0f));


	//LightSource
	//    Seen from below light:
	//    a-----b           ^ x
	//    | \   |           |
	//    |   \ |           ----> y
	//    c-----d

	Vertex a(1.f, -1.f, 0.0f, 1.0f);
	Vertex b(1.0f, 1.0f, 0.0f, 1.0f);
	Vertex c(-1.f, -1.f, 0.0f, 1.0f);
	Vertex d(-1.f, 1.f, 0.0f, 1.0f);

	Triangle lightTri1(a, c, d, ColorDbl(255.0));
	Triangle lightTri2(a, d, b, ColorDbl(255.0));
	
	std::vector<Triangle> lightTriangles = { lightTri1, lightTri2 };
	LightSource light(lightTriangles, 2, Vertex(6.0f, 0.0f, 4.999f, 1.0f), 2.0);

	Vertex eye1(-2.0f, 0.0f, 0.0f, 1.0f);
	Vertex eye2(-1.0f, 0.0f, 0.0f, 1.0f);

	Camera cam(eye1, eye2, 800, 800);
	Scene scene;

	scene.addObject(tetrahedron);
	scene.addObject(sphere);
	scene.addLightsource(light);

	cam.switchEye();
	cam.render(&scene);
}