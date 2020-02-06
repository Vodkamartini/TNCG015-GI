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
	
	int material = currentNode->ray.getIntersection().materialType;
	
	// To avoid endless ray-tracing we kill of some rays if we have diffuse reflectors (aka Russian Roulette)
	if (material == LAMBERTIAN) {
		float random = std::rand() / RAND_MAX;
		float killRisk = (depth != 0) ? 0.2f : 0.0f;	// Might be a better value
		if (random < killRisk)
			return;
	}

	switch (material) {
		case PERFECT_REFLECTOR:
			currentNode->reflected = new Node(currentNode, perfectReflection(currentNode->ray), scene);
			createNewRayNodes(currentNode->reflected, ++depth);
			break;
		default : 
			currentNode->reflected = new Node(currentNode, Ray(), scene);
			break;
	}

	currentNode->reflected = new Node(currentNode, currentNode->ray, scene);

}

Ray RayTree::diffuseReflection(Ray& in) {
	return Ray();
}

Ray RayTree::perfectReflection(Ray& in) {
	Direction reflection = glm::reflect(in.getDirection(), in.getIntersection().normal);
	Direction offset = 0.00001f * in.getIntersection().normal;	// Use offset for false self-intersections
	Vertex reflectionOrigin = Vertex(in.getIntersection().position + glm::vec4(offset, 1.0f));
	return Ray(reflectionOrigin, glm::vec4(reflection, 1.0f));
}

void RayTree::destroyNode(Node* node) {
	if (node) {
		destroyNode(node->reflected);
		delete node;
	}
}

void RayTree::destroyNodeTree(Node* root) {
	destroyNode(root->reflected);
}