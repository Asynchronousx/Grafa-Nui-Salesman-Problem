// Grafa-Nui.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "class_graph.h"

int main()
{
	UndirectedGraph Grafa_nui;
	Grafa_nui.createRealm();
	Grafa_nui.CalculateDistance();
	Grafa_nui.printFile();
}
