#ifndef RAYTREE_H
#define RAYTREE_H

#include "Ray.h"
#include "Scene.h"


class RayTree {
public:
	RayTree(Scene* sceneIn) : scene(sceneIn) {};
	~RayTree() {};

	ColorDbl trace(Ray& ray);

private:

	struct Node {
		Node(Node* parentIn, Ray rayIn, Scene* scene) 
			: parent(parentIn), reflected(nullptr), refracted(nullptr), ray(rayIn) {
			scene->detectIntersection(ray);
		}

		Node* parent;
		Node* reflected;
		Node* refracted;
		Ray ray;
		float reflectionCoefficient = 1.0f;
	};
	Scene* scene;
	const int MAX_DEPTH = 1;
	Node createRayTree(Ray& ray);
	void createNewRayNodes(Node* currentNode, int depth);

	void destroyNode(Node* node);
	void destroyNodeTree(Node* root);
};

#endif // !RAYTREE_H
