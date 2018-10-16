#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "class_node.h"
#include "class_edge.h"


class UndirectedGraph {
private:
	//Member:
	std::vector<Node*> VertexSet;
	std::vector<Edge*> EdgeSet;
	std::vector<float> AdjMatrix;
	std::vector<int>  BestOptimalPath;
	std::vector<int>  BestGreedyPath;
	float BestOptimalDist;
	float BestGreedyDist;

	//Functions:
	void addGraphVertex(int numericValue, std::pair<float, float> Coordinates); 
	void updateADJMatrix(Node* First, Node* Second, float Distance);
	void fillADJMatrix(std::vector<std::pair<float, float>> Distances);
	void unmarkVisited();
	float Tract(std::pair<float,float> X, std::pair<float, float> Y);

	//Distance Functions
	void NearestNeighbour();
	int MinimumLocalDistance(int Row, float& totalDistance);
	void BackTrackingUTILITY();
	void BackTracking(float BestBacktrackDist, int Npath, int previousVertex, std::vector<int> ActualPath);

	//Filestream Functions
	bool file_check(const char *fileName);
	void createGraphFromFile();
	void addOutputInformation();
	void printOutputInformation();

	//Methods: Set
	void setMatrix(int MatrixSize);
	void setNode(Node* newNode);
	void setEdgePair(Edge* newEdge);
	void setMatrixElement(int Index, float Distance);
	void setBestOptimalDist(float BestOptimalDist);
	void setBestGreedylDist(float BestGreedyDist);
	void setOptimalPath(std::vector<int> BestOptimalPath);
	void setOptimalPathIsle(int Isle);
	void setGreedyPath(std::vector<int> BestGreedyPath);
	void setGreedyPathIsle(int Isle);

	//Methods: Get
	std::vector<Node*> getVertexSet();
	std::vector<Edge*> getEdgeSet();
	std::vector<float> getAdjMatrix();
	std::vector<int>  getBestOptimalPath();
	std::vector<int>  getBestGreedyPath();
	int getMatrixWidth();
	float getBestOptimalDist();
	float getBestGreedyDist();

public:
	//Constructor
	UndirectedGraph() { ; } //Default
	~UndirectedGraph() { ; } //Destructor

	//Helper Functions: 
	//Here we use some helper function to grant the access to private
	//methods in the class.

	//Helper Functions
	//Helper function that, given a .txt file with the number of isles,
	//and their coordinate, will create the grafa-nui realm.
	void createRealm();
	
	//Helper function that will calculate the distance with the Nearest
	//Neighbour algorithm and the backtracking method.
	void CalculateDistance(); 

	//Helper function to print the information on the an output.txt file
	//and display that on the screen.
	void printFile(); 

};
