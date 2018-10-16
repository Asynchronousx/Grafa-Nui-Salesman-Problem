#pragma once
#include <iostream>

class Node {
private:
	char Value; //represent the isle value
	std::pair<float, float> Coordinates; 
	bool isVisited;

public:
	//Constructor:
	Node() { ; } //Default 
	Node(char startValue, std::pair<float, float> newCoordinates) : Value(startValue), 
		isVisited(false), Coordinates(newCoordinates) { ; } //Inizialization parameter list
	~Node() { ; } //Destructor

	//Methods: Set
	void setCoordinate(std::pair<float, float> Coordinates) { this->Coordinates = Coordinates; }
	void setValue(char Value) { this->Value = Value; } 
	void setVisited(bool isVisited) { this->isVisited = isVisited; }

	//Methods: Get
	char getValue() { return Value; } 
	bool getIsVisited() { return isVisited; }
	std::pair<float, float> getCoordinates() { return Coordinates; }

};
