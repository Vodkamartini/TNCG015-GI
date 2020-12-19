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


	//LightSource
	//    Seen from below light:
	//    a-----b           ^ x
	//    | \   |           |
	//    |   \ |           ----> y
	//    c-----d

	Vertex a(0.5f, -0.5f, 0.0f, 1.0f);
	Vertex b(0.5f, 0.5f, 0.0f, 1.0f);
	Vertex c(-0.5f, -0.5f, 0.0f, 1.0f);
	Vertex d(-0.5f, 0.5f, 0.0f, 1.0f);

	Triangle lightTri1(a, c, d, ColorDbl(255.f, 0.f, 255.f));
	Triangle lightTri2(a, d, b, ColorDbl(255.f, 0.f, 255.f));
	
	std::vector<Triangle> lightTriangles = { lightTri1, lightTri2 };
	LightSource light(lightTriangles, 2, Vertex(5.0f, 0.0f, 4.99f, 1.0f));

	Vertex eye1(-2.0f, 0.0f, 0.0f, 1.0f);
	Vertex eye2(-1.0f, 0.0f, 0.0f, 1.0f);

	Camera cam(eye1, eye2, 800, 800);
	Scene scene;

	scene.addTetrahedron(tetrahedron);
	scene.addSphere(sphere);

	scene.addLightsource(light);

	cam.switchEye();
	cam.render(&scene);
}