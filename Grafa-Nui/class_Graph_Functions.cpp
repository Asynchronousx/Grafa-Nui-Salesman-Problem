#include "stdafx.h"
#include "class_graph.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
#include <math.h>

//Function that add a Vertex (Isle) to our Map.
void UndirectedGraph::addGraphVertex(int numericValue, std::pair<float, float> Coordinates) {
	//if the graph is empty 
	if (getVertexSet().empty()) { 
		//If there's no node into the graph, so insert the capital 
		char Value = 'C'; 
		//Reserving V[0] to the Capital, and its coordinates.
		Node* newNode = new Node(Value,Coordinates); 
		//Pushing the node 
		setNode(newNode);

		//No need to use delete; newNode has reached it's
		//maximum lifetime when exiting from the scope, 
		//the Destructor will delete the object and it's 

	}
	else { //if there's at least 1 element
		//conversion from int to char adding '0'
		char Value = numericValue + '0'; 
		//create a new node and setting the coordinates.
		Node* newNode = new Node(Value,Coordinates); 

		//Pushing the node
		setNode(newNode);
		
		//Creating the edges with the new node with every other nodes in the graph:
		//we're operating with full connected and undirected graph.
		std::vector<Node*> TMPVertexSet = getVertexSet();
		std::vector<Node*>::iterator it;

		//For every node in the graph except the last node inserted
		for (it = TMPVertexSet.begin(); it !=TMPVertexSet.end()-1; it++) {
			//create a new edge
			Edge* newEdge = new Edge(); 
			//push at every iteration information about the newnode and every other node in the graph
			newEdge->setEdge(*it, newNode, Tract((*it)->getCoordinates(), newNode->getCoordinates())); 
			//set normal edge (NewNode -- It and reverse: It -- NewNode)
			setEdgePair(newEdge);
		}

		//No need to use delete; newNode and newEdge
		//have reached their maximum lifetime when exiting 
		//from the scope, the Destructors will delete the 
		//objects and their memory referement.
	}
}

//Function that helps the values to find the right place into the Adjacence matrix.
void UndirectedGraph::updateADJMatrix(Node* First, Node* Second, float Distance) {

	//We're operating on a 1D vector as a 2D one. 
	//So we need firstly to find the Row (the position of the first node)
	//And the column, (the position of the second node) to work with.
	std::vector<Node*> TMP = getVertexSet();
	int Row = std::distance(TMP.begin(), std::find(TMP.begin(), TMP.end(), First));
	int Column = std::distance(TMP.begin(), std::find(TMP.begin(), TMP.end(), Second));

	//setting 0 in the correspective cells node (0,0), (1,1), (2,2) etc,
	//because a node dist 0 from itself. (All the diagonals values are 0).
	setMatrixElement(getMatrixWidth()*Row + Row, 0);
	setMatrixElement(getMatrixWidth()*Column + Column, 0);

	//Setting the distance values between first and 
	//second node into the ADJMatrix with the formula:
	//Width*Row+Column: this is the formula to work with 1D
	//Vectors like a 2D One: is equivalent to write: Vector[Row][Column].
	setMatrixElement(getMatrixWidth()*Row + Column, Distance);
	setMatrixElement(getMatrixWidth()*Column + Row, Distance);	

}

//Function that given the vector of the distance taken from the file, creates the ADJ Matrix.
void UndirectedGraph::fillADJMatrix(std::vector<std::pair<float, float>> Coordinates) {

	//For the size of the Coordinates Vector
	for (size_t i = 0; i < Coordinates.size(); i++) {
		//For the size of the Coordinates Vector-1, incrementing i+1 every step,
		//we only need to iterate twice, because the matrix is symmetric.
		for (size_t j = i+1; j < Coordinates.size(); j++) {
			//Distance: Euclidean distance between two points.
			float Distance = Tract(Coordinates.at(i), Coordinates.at(j)); 
			//update the matrix with the right distance.
			updateADJMatrix(getVertexSet().at(i), getVertexSet().at(j), Distance); 
		}
	}
}

//Function that mark all the visited node as Unvisited.
void UndirectedGraph::unmarkVisited()
{
	std::vector<Node*> TMPVertexSet = getVertexSet();
	std::vector<Node*>::iterator it; 
	for (it = TMPVertexSet.begin(); it != TMPVertexSet.end(); it++) {
		(*it)->setVisited(false);
	}
}

//Function that calculate the Euclidean formula within 2 points in the same space.
float UndirectedGraph::Tract(std::pair<float, float> X, std::pair<float, float> Y) {
	//Math formula to calculate the distance between two point
	return sqrt(pow(Y.first - X.first, 2) + pow(Y.second - X.second, 2));
}


//-----------------DistanceFunction:-----------------
//                 NearestNeighbour

//Function based on a greedy approssimation, at every
//iteration will choose the shortes isle distance to 
//calculate a sub-optimal path from the capital to 
//every other isles.
void UndirectedGraph::NearestNeighbour() {

	//creating an ActualPath to store the path choosen by NN Algorithm
	std::vector<int> ActualPath;

	//Useful Variables
	float totalDistance = 0;
	std::vector<Node*> TMPVertex = getVertexSet();
	std::vector<float> ADJTmp = getAdjMatrix();

	//Capital (Vertex[0]) is the first node visited	
	//1)Choose the capital as the actual node:
	//bestlocal is the best local node with the best value (starting at the capital)
	int BestLocal = 0;
	//set the capital visited
	TMPVertex.at(0)->setVisited(true);

	//1)Adding the capital to the actual path:
	//This action will be performed on the output function, 
	//because we cant add a char to an int vector.
	//The only thing we care here is the distance.

	for (size_t i = 0; i < TMPVertex.size() - 1; i++) {
		//Found who's node distance is the smaller and update the distance:
		//2)Choose the minimum distance isle
		BestLocal = MinimumLocalDistance(BestLocal, totalDistance);

		//3)Adding the isle to the path
		ActualPath.push_back(TMPVertex.at(BestLocal)->getValue() - '0');

		//4)bestlocal is now the current isle

		//5)Set actual isle node as visited
		TMPVertex.at(BestLocal)->setVisited(true);

		//6)we'll check if there are more isle to analyze 
		//in the next for.
	} 
	

	//7) adding the distance from the last node to the capital
	totalDistance += ADJTmp.at(getMatrixWidth() * 0 + BestLocal);
	
	//8) Adding the solution
	setBestGreedylDist(totalDistance); //updating best greedy distance
	setGreedyPath(ActualPath); //updating best greedy path
	
	unmarkVisited(); //Restoring all the isles as not visited

}


//Function useful to calculate in every iteration of the NN algorithm 
//the minimum local distance choice we can take.
int UndirectedGraph::MinimumLocalDistance(int Row, float& totalDistance) {

	//Useful variables
	std::vector<float> AdjTMP = getAdjMatrix();
	int Width = getMatrixWidth();

	//At the beginning, the minimum distance is infinity.
	float MinimumDistance = INT_MAX;
	//The index we'll need to know who's the lowest choice.
	int Index;

	//For the width of the ADJ Matrix (number of vertex)
	for (size_t i = 0; i < getMatrixWidth(); i++) {
		//if the distance is minor than the previous and the node is not visited
		if (AdjTMP.at(Width*Row + i) < MinimumDistance && !getVertexSet().at(i)->getIsVisited()) {
			//update minimum distance 
			MinimumDistance = AdjTMP.at(Width*Row + i);
			//update the index
			Index = i;
		}
	}
		
	//Updating the total distance
	totalDistance += MinimumDistance;
	return Index;

}


//-----------------DistanceFunction:-----------------
//                   BackTracking


//Utilty Function for the BackTracking:
//We're declaring NPath (number of isles visited),
//ActualDist, initially set to 0, previous Vertex, useful
//to take track of the Isle needed to be analyzed, 
//and ActualPath, the path that is filled in every 
//iteration and recursion call with the right path.
void UndirectedGraph::BackTrackingUTILITY() {

	int NPath = 1;
	int previousIsleIndex = 0;
	float ActualDist = 0;
	std::vector<int> ActualPath;
	//setting the capital as visited (we're moving from there)
	getVertexSet().at(0)->setVisited(true); 
	//push the capital into the "actual path"
	//This action will be performed on the output function, 
	//because we cant add a char to an int vector.
	//The only thing we care here is the distance.
	
	//Best Optimal Dist = Best Greedy Dist
	setBestOptimalDist(getBestGreedyDist()); 

	//Backtracking
	BackTracking(ActualDist, NPath, previousIsleIndex, ActualPath);
	
	//After we're done, unmark all the visited vertex.
	unmarkVisited();

}

//Function that use the backtracking to calculate the best optimal distance from all the isles.
void UndirectedGraph::BackTracking(float ActualDist, int NPath, int previousIsleIndex, std::vector<int> ActualPath) {

	//For all the Adjacent Isles
	for (int i = 1; i < getVertexSet().size(); i++) { 
		//If an Adjacent isle is not visited
		if (!getVertexSet().at(i)->getIsVisited()) { 

			//Take the coordinate of the current, previous and capital isle
			std::pair<float, float> previousIsle = getVertexSet().at(previousIsleIndex)->getCoordinates();
			std::pair<float, float> currentIsle = getVertexSet().at(i)->getCoordinates();
			std::pair<float, float> Capital = getVertexSet().at(0)->getCoordinates();

			//If actual dist + Tract(current, previous) + return to the capital < Best Dist
			if (ActualDist + Tract(previousIsle, currentIsle) + Tract(currentIsle, Capital) < getBestOptimalDist()) { 
				//visit the isle 
				getVertexSet().at(i)->setVisited(true);
				//push the isle into the actual path (update the path)
				ActualPath.push_back(getVertexSet().at(i)->getValue() - '0'); 
				//Backtracking with the new isle
				BackTracking(ActualDist + Tract(previousIsle, currentIsle), NPath + 1, i,ActualPath);
				//***Returning from the backtracking***
				//set the isle not visited, because is not useful 
				getVertexSet().at(i)->setVisited(false);
				//pop the Isle from the bath
				ActualPath.pop_back();
			}
			else { // else actual dist + tract + return is major than Best Dist
				return; //not interested, return to the previous call 
			}
		} // if there are no more isles to analyze
		else if (NPath == getVertexSet().size()) { 
			//and if the actual dist is < than the actual best dist
			if (ActualDist < getBestOptimalDist()) { 
				//push last isle: returning to the capital
				//This action will be performed on the output function, 
				//because we cant add a char to an int vector.
				//The only thing we care here is the distance.

				//update the optimal path 
				setOptimalPath(ActualPath); 
				//set the best distance found:
				std::pair<float, float> LastIsle = getVertexSet().at(previousIsleIndex)->getCoordinates();
				std::pair<float, float> Capital = getVertexSet().at(0)->getCoordinates();
				setBestOptimalDist(ActualDist + Tract(LastIsle, Capital)); 
			}

			//return to previous call
			return; 
		}		
	}

	// we are done; return to the previous call if nothing else can be done, 
	//or return from the function itself if there is nothing more to analyze.
	return;
}


//-----------------Filestream Function-----------------

//File check to know if such file called "Coordinate" does exists.
bool UndirectedGraph::file_check(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}


//Function that, given an input with:
//N at first line, 
//Coordinates at the next,
//Will create a graph with those charateristic.
void UndirectedGraph::createGraphFromFile() {


	std::ifstream input;

	if (file_check("Coordinate.txt")) {
		//try to open the file
		do {
			//clean the buffer
			input.clear();
			//open the coordinates
			input.open("Coordinate.txt");
		} while (!input); //while no input opened
	} else {
		std::cout << "No such file named 'Coordinate' was found." << std::endl;
		std::cout << "Try to place a file named 'Coordinate' into the project folder," << std::endl;
		std::cout << "Then try again to run this program." << std::endl;
		exit(EXIT_FAILURE);
	}

	//Declaration of useful variables:
	//numeric value useful to take track of the 
	//name of the isles automatically generated
	int numericValue = 0; 
	//Number of the isles
	int NumberOfIsle; 
	//coordinate of the isles
	std::vector<std::pair<float, float>> Coordinates; 
	//point P(x,y)
	float x, y; 

	//getting the number of the isles
	input >> NumberOfIsle; 
	//creating the ADJ matrix (with number of isles + 1 (capital))
	setMatrix(NumberOfIsle + 1); 
    
	//Pushing back the distance of the capital to herself: 0,0
	Coordinates.push_back(std::make_pair(0, 0));

	//while there's something to analyze
	while (input >> x >> y) { 
		//pushback x,y as the point
		Coordinates.push_back(std::make_pair(x, y)); 
	}

	//Creating many nodes ad the isle number in the file + 1 (the capital)
	for (size_t i = 0; i <= NumberOfIsle; i++) {
		addGraphVertex(numericValue, Coordinates.at(i));
		numericValue++;
	}

	//fill the adj matrix with the coordinate obtained
	fillADJMatrix(Coordinates); 

	//closing the input 
	input.close();
}

//Function that at the end of the program, will put all the information discovered 
//on an output.txt file.
void UndirectedGraph::addOutputInformation() {
	
	//create an output.txt file
	std::ofstream output("Output.txt");

	//stamp the information about optimal sub-path (choosen with greedy approssimation)
	output << "Optimal sub-path: ";
	output << "C ";
	for (auto x : getBestGreedyPath()) {
		output << x << " "; 
	} output << "C ";
	output << std::endl;
	output << "Distance = ";
	output << std::setprecision(5) << getBestGreedyDist() << " km";

	output << std::endl << std::endl;

	//stamp the information about the optimal path (choosen with backtracking)
	output << "Optimal path: ";
	std::vector<int> PathTMP = getBestOptimalPath();
	std::vector<int>::reverse_iterator r_it;
	output << "C ";
	for (r_it = PathTMP.rbegin(); r_it != PathTMP.rend(); r_it++) {
		output << (*r_it) << " ";
	} output << "C ";
	output << std::endl;

	output << "Distance = ";
	output << std::setprecision(5) << getBestOptimalDist() << " km";
	output << std::endl << std::endl;

	output << "Greedy Path / Optimal Path = ";
	output << std::setprecision(3) << getBestGreedyDist() / getBestOptimalDist();

	//close the output, we dont need it anymore.
	output.close();

}

//Function that open the output file and prints it's content.
void UndirectedGraph::printOutputInformation() {

	std::ifstream input;

	std::cout << "Printing the information wrote on output.txt: " << std::endl << std::endl;
	
	//open the file 
	do {
		input.clear();
		input.open("output.txt");
	} while (!input);

	std::string line;

	//while there's something to take from the file 
	while (std::getline(input, line, '\n')) {
		std::cout << line << std::endl;
	} std::cout << std::endl;
	
	//close the file
	input.close();

}


//Methods:

//Methods: Set
void UndirectedGraph::setMatrix(int MatrixSize) {
	std::vector<float> AdjM(MatrixSize*MatrixSize, -1);
	this->AdjMatrix = AdjM;
}
void UndirectedGraph::setNode(Node* newNode) {
	this->VertexSet.push_back(newNode); 
}

void UndirectedGraph::setEdgePair(Edge* newEdge) {
	this->EdgeSet.push_back(newEdge);
}

void UndirectedGraph::setMatrixElement(int Index, float Distance) {
	this->AdjMatrix.at(Index) = Distance; 
}

void UndirectedGraph::setBestOptimalDist(float BestOptimalDist) {
	this->BestOptimalDist = BestOptimalDist; 
}

void UndirectedGraph::setBestGreedylDist(float BestGreedyDist) {
	this->BestGreedyDist = BestGreedyDist; 
}

void UndirectedGraph::setOptimalPath(std::vector<int> BestOptimalPath) {
	this->BestOptimalPath = BestOptimalPath; 
}

void UndirectedGraph::setOptimalPathIsle(int Isle) {
	this->BestOptimalPath.push_back(Isle); 
}

void UndirectedGraph::setGreedyPath(std::vector<int> BestGreedyPath) { 
	this->BestGreedyPath = BestGreedyPath; 
}

void UndirectedGraph::setGreedyPathIsle(int Isle) {
	this->BestGreedyPath.push_back(Isle); 
}

//Methods: Get
std::vector<Node*> UndirectedGraph::getVertexSet() { return VertexSet; }
std::vector<Edge*> UndirectedGraph::getEdgeSet() { return EdgeSet; }
std::vector<float> UndirectedGraph::getAdjMatrix() { return AdjMatrix; }
std::vector<int>  UndirectedGraph::getBestOptimalPath() { return BestOptimalPath; }
std::vector<int>  UndirectedGraph::getBestGreedyPath() { return BestGreedyPath; }
int UndirectedGraph::getMatrixWidth() { return std::sqrt(getAdjMatrix().size()); }
float UndirectedGraph::getBestOptimalDist() { return BestOptimalDist; }
float UndirectedGraph::getBestGreedyDist() { return BestGreedyDist; }


//Helper Function: 
//Functions that will call private function
//in this class.

//Function that will create a realm from an input coordinate file.
void UndirectedGraph::createRealm() {
	createGraphFromFile();
}

//Function that will calculate the Path (optimal and suboptimal)
//and then write that into a file.
void UndirectedGraph::CalculateDistance() {
	NearestNeighbour();
	BackTrackingUTILITY();
	addOutputInformation();
}

//Function that print the information about a created output.
void UndirectedGraph::printFile() {
	printOutputInformation();
}