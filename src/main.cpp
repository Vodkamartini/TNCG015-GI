#include "Scene.h"
#include "Camera.h"



int main() {
	Scene* scene;
	scene = new Scene();
	scene->createRoom();
	
	Camera cameron;
	cameron.render(scene);
	cameron.createImage();
	return 0;
}