#include "RayTree.h"


RayTree::Node RayTree::createRayTree(Ray& ray) {
	Node root = Node(nullptr, ray, scene);
	Node* next = &root;

	createNewRayNodes(&root, 0);

	return root;
}

ColorDbl RayTree::trace(Ray& ray) {
	Node root = createRayTree(ray);
	
	ColorDbl pixelColor = root.ray.getIntersection().color;
	destroyNodeTree(&root);
	return pixelColor;
}

void RayTree::createNewRayNodes(Node* currentNode, int depth) {
	//TODO: Russian roulette
	float n1 =0.f, n2 = 0.f;
	Ray refractedRay = Ray();

	currentNode->reflected = new Node(currentNode, currentNode->ray, scene);

}

void RayTree::destroyNode(Node* node) {
	if (node) {
		destroyNode(node->reflected);
		destroyNode(node->refracted);
		delete node;
	}
}

void RayTree::destroyNodeTree(Node* root) {
	destroyNode(root->reflected);
	destroyNode(root->refracted);
}