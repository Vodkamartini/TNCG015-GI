#ifndef RAYTREE_H
#define RAYTREE_H

#include "Ray.h"
#include "Scene.h"


class RayTree {
public:

private:


	struct Node {
		Node(Node* parentIn, Ray rayIn, Scene* scene) 
			: parent(parentIn), reflected(nullptr), refracted(nullptr), ray(rayIn) {
		
		}


		Node* parent;
		Node* reflected;
		Node* refracted;
		TriangleIntersection intersection;
		Ray ray;
		float reflectionCoefficient = 1.0f;
	};
	Scene* scene;
	const int MAX_DEPTH = 1;


};

#endif // !RAYTREE_H
