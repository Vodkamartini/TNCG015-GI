#include "Scene.h"
#include "Camera.h"
#include <iostream>


int main() {
	Scene* scene;
	scene = new Scene();
	scene->createRoom();
	std::cout << "Triangles in scene: " << scene->getTriangles() << std::endl;
	
	Camera cameron;
	cameron.render(scene);
	cameron.createImage();
	return 0;
}