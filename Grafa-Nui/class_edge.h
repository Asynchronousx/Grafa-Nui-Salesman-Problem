#pragma once
#include <iostream>
#include "class_node.h"

class Edge {
private:
	std::pair<Node*, Node*> normalEdge; //example : Edge between node: A - B  \___ fully connected 
	std::pair<Node*, Node*> inverseEdge; // example: Edge between node: B - A /
	float Weight;

public:
	//Constructor
	Edge() { ; } //Default
	Edge(Node* firstNode, Node* secondNode, float inputWeight) : //Initialization parameter list
		normalEdge(std::make_pair(firstNode,secondNode)), Weight(inputWeight) { ; }
	~Edge() { ; } //Destructor

	//Methods: Set
	void setEdge(Node* firstNode, Node* secondNode, float Weight = 0) {
		//Filling first edge pair
		this->normalEdge.first = firstNode;
		this->normalEdge.second = secondNode;
		//Filling the inverse edge pair
		this->inverseEdge.first = secondNode;
		this->inverseEdge.second = firstNode;
		//Filling the weight
		this->Weight = Weight;
	}

	//Methods: Get 
	std::pair<Node*, Node*> getNormalEdge() { return normalEdge; }
	std::pair<Node*, Node*> getInverseEdge() { return inverseEdge; }
	int getWeight() { return Weight; }

};