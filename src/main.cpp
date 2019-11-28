#include "Scene.h"
#include "Camera.h"
#include <iostream>


int main() {
	Scene* scene;
	scene = new Scene();
	scene->createRoom();
	scene->addTetrahedron();
	scene->addImplicitSphere();
	std::cout << "Triangles in scene: " << scene->getTriangles() << std::endl;
	std::cout << "Spheres in scene: " << scene->getImplicitSpheres() << std::endl;
	
	Camera cameron;
	cameron.render(scene);
	cameron.createImage();
	return 0;
}