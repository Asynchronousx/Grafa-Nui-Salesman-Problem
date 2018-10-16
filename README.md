# Grafa-Nui-Salesman-Problem
The Realm of Grafa-Nui It is composed of a main island, where there is the Capital, and by N Smaller islands, all with a small Airport. After having represented on a map the islands, the king wants to organize a control tour of its governors, by plane, but it wants to save time and fuel by appropriately choosing the order of visit of the N Islands, starting from the capital and returning home to the End of the round.  

# Problem: 
	Using the Greedy approximation technique of the neighbor Nearest, which is each time to choose the nearest island that has not yet been visited, describe in pseudocode the algorithm that calculates the path Sub-Optimal with relative distance D1 and you implement it in C++. 
	Using an algorithm based on backtracking technique, calculate the optimal path between all possible sequences, with total distance D2. 
	Evaluate the ratio between the distances obtained by the two methods, that is, the Greedy algorithm Maggiora the optimum minimum distance. 

# Input data:
A text file containing the first staff is assigned The number N of the islands (Beyond the capital);
The N successive Righi Contain the Cartesian coordinates X Y (2 values separated by a space) of the islands relative to the capital (which has coordinates (0; 0)).

# Recruitment: 
1 ≤ N ≤ 20
All the islands are located less than 150 Km from the capital, therefore the terrestrial curvature can be neglected, considering a flat map with a system of Orthal Cartesian axes (Euclidean distances between the knots); 
We consider the islands indexed by [1] to [N]; The index [0] can be reserved for the capital.
Save the results obtained on Output. txt. 

      Examples:

 


# Introduction.

For the problem of Sovereign Traveler, the data structure that is most useful to solve this particular problem, is that of the graph. 

# Graphs.
Formally, a graph G, It is a set composed of a pair (V, E), Where:
	V is a finite set of elements, called Vertices.
	E is a finite set of a pair of vertices, called Arches.
in which, n Denotes the number of vertices in the graph, and is represented as n = |V|                    While m Denotes the number of arcs in the graph, and is represented as m = |E|


We can also define and distinguish two types of graphs:
	Direct graphs.
	Indirect graphs.

# Direct graphs.
Direct graphs, are structures NELle such as the Arches have a direction of travel: In this case, you can move from one knot to another, but not vice versa (following the direction of travel).

 

In this graph, every InvitationAnd is represented by a number, while each ArCo It is represented by an arrow that connects two vertices. The direction of travel of an arrow indicates that a graph is Direct, that is, you can move between the vertices by following only The Order of travel Proposed in the image.

# Indirect graphs.
The indirect graphs, are structures in which the Arches Do not have a direction of travel: You can then move from one knot to another without worrying about the direction of the arc. (a structure that refers to most real problems).

 
As we can see, the Difference with the direct graph is instantaneous: the ArchThe Do not represent arrows (so do not have to travel) But simple lines Linking two Vertices; This means that We could move from two any vertices connected to each other without any problem.
We can also add, that two Vertices Connected by a Arc are defined as "vIcini", or"Neighbour". 
Graphs and weight function.
Given a graph G = (V, E), It will define its weight function as w:E→R  That associates a weight with each arc, represented by a real number.
By associating to each arc a weight, you will get a Weighing graph:
 
Each arc will therefore have its cost of travel, introducing the concept of the paths in a graph: The weight of a path p=(v_0,…,v_k ) is given by the sum of the weights of the arches that make up w(p)=∑_(i=1)^k▒(w(v_(i-1),v_i )) . 
For example, a path from 0 to 4,  p=(0,1,4)  He will have weighed w(p)= 2.

# Connecting a graph.
In an unoriented graph G = (V, E), Two vertices U e V are connected Between them, If in G There is a path between U e V. Otherwise, they are not connected. A graph is connected if any pair of vertices u And v Distinct of the graph is connected. Here is an example.

Graph DiscIs 				Connected graph.
  

# Graph weakly Connected
A graph oriented (Directed graph) is said weakly connected (Weakly connected) If replacing All oriented bows With unoriented Bows You get an indirect connected graph. This is because, if we exchanged the order of the arcs between two or more nodes, it might be impossible to go from one vertex to another because of the orientation of the arcs. 

# Graph strongly Connected.
A graph is said Strongly connected (Strongly connected) if it contains a Path oriented (That moves from From U a V And vice versa, so not necessarily with the arrows), From U a V For each pair of vertices u,v. 
Below, a graphical example, considering the non-oriented graph taken into analysis before:

 
How can we well denote from the graph, There is a path oriented From U a V, For any pair of vertices u,v. We can then move from one vertex of the graph to any other vertex, with the result that each vertex is “vEar", or"Neighbour"than any other vertex. 
In a strongly connected graph also, Being all the vertices connected to each other with an arc, the total number of the Arches will be equal to |E| = N (N-1)/2.
For the resolution of the problem of the ruler, we will adopt this type of data structure: A graph that is not oriented, strongly connected. 


# Representation of a graph
To represent a graph G = (V, E), We employ two methodologies useful to transcribe the data structure in memory: 
	Adjacency lists
	adjacency arrays.
Both methods of description work both for the type of graphs oriented, and for those that are not oriented. 
How do you choose a correct graph description mode?
The decision will be made based on the type of graph with which we are going to operate. 

# Adjacency lists
The adjacency lists Provide a compact way of representing The Scattered graphs: each Vertex will keep a list identifying which vertices are adjacent to him.                                                        A graph G = (V, E) It is said Spread If | E | is less than | V |2, That is, if the number of arcs is in a distinct minority from the number of high vertices squared. 

Adjacency List of a oriented graph:
 

Adjacency List of an unoriented graph:
 

# Matrix of adjacency.
adjacency arrays are more useful and read if we were dealing with Graphs dense, Or if you need to have a quick response on the connection state of two vertices to each other through an arc. Adjacency matrices are formed by | V |2  Elements, to indicate whether there is a connection between a given vertex i With a given vertex j. 
to the index Matrix [i] [j] You will then find the answer to this question, in which it will be stored 1 (or the weight of the arc of the vertices in Question If The connection exists, or 0 if it does not exist No connection between those two vertices. È To note well That a vertex is not adjacent to itself, and then in the index Matrix [i] [j], where i = J  Find The value 0.
Also, adjacency arrays for non-oriented graphs are symmetrical, or To rebuild The entire matrix will be possible to take into account Only the part that is At the top of theThe diagonal in The matrix (which are always square).
A graph G = (V, E) It is said Dense If | E | It touches the values of | V |2, That is, if the number of arcs is almost equal to the number of vertices squared.

Adjacency arrays in a oriented graph:
 

adjacency arrays in an unoriented graph
 
For the resolution of the problem of the sovereign viaggator, We will adopt this type of representation for our structure Data: A Symmetric adjacency Matrix of a fully connected and dense indirect graph.

# Nearest Neighbor Algorithm.

# Introduction.
Let's now analyze The first method of resolution For the problem of the sovereign traveler.
The Nearest Neighbor Algorithm OrAlgorithm of the nearest neighbor") is an algorithm based onGreedy approximation. 
The substantial difference between A greedy approximation and one Greedy technique is the presence of the optimal substructure: in the approximation Greedy In fact, lacking the Excellent substructure, we may have access to a Sub-optimal solution; 
The greedy technique instead, enjoying the Excellent substructure properties will give life to a Optimal solution.

# History.
The next neighbor's algorithm, was one of the first developed to determine a solution to the problem of Salesman: In this problem, the salesman begins his visit to A city in Case To sell its products, and Continue to visit all the cities To visit In order of the shortest distance; Will move from one city to another choosing the one "Nearest" In terms of distance, Until all the cities are visited. 
Being a greedy approximation algorithm, Will not lead to an optimum solution, but it will be particularly Fast and performing.

# Implementation and use.
The next neighbor's algorithm Applied to the problem of the traveler sovereign so, it's easy to implement and fast-running, as It consists of every step of choosing the nearest island until all these are finished:
	We fix the capital
	Choose the Island K That has not been visited
	Add to Path The stretch Current-> K
	Fix K What Current knot
	We mark K AsVisited”
	If there are other islands Do not visit, Back to step 2
	Add To Route the return stroke to the capital
	The path found is the solution.

Below, we find the pseudo-code:
 

To give a graphical example, consider the following graph, not oriented and completely connected:

 
Our capital in this case will be 1; From here we begin our visit to find the best "sub-optimal" path through the procedure of Nearest Neighbour.
We add 1 to our current path, and we look for the nearest island not visited that presents the lesser distance: 
 
In this case, as you can clearly see from the graph in question, the nearest island not yet visited is The number 2 So let's add the island to the path, and update the best distance found with the stretch from Island 1 to Island 2:
 
From here we carry out the same procedure used previously because the islands to be analyzed are not finished yet: the nearest island not yet visited is The number 4 So let's add the island to the path, and update the best distance found with the stretch from Island 2 to island 4:
 
From here we carry out the same procedure used previously because the islands to be analyzed are not finished yet: the nearest island not yet visited is The number 3 Then we add The island to the path, and we update the best distance found with the stretch from Island 4 to island 3 
Now that we have analyzed each island, and so each of them has been visited, we must return to the capital (our number one island). Then we leave the cycle and add the path from the last island visited the capital, also updating the distance.
 
The algorithm ends, it is the best distance found is 17.
Of course, being a solution Sub-Optimal, It means that in a plausible way it is not the best you can find; In this case, to find the best solution to the problem of the sovereign traveler, we will entrust ourselves to the technique of Backtracking.



# Backtracking.

# Introduction.
Backtracking (which in Italian can be defined as "backwards monitoring") is a programming technique for finding solutions to problems where they must be Necessarily satisfied with the constraints. This technique is useful when there sIano to be taken A series of Discreet choices; These choices may seem optimal on time, But once you go to the bottom of the problem solving, it could be said that the choices made earlier were not right, With a need to go back to the last known valid solution. 
And this is where backtracking shows its strength: this technique Enumerates all possible solutionsAnd Discard Those that Do not meet the constraints.
Structure.
Backtracking, has a structure of resolution similar to that of a tree structure: it keeps track of all the nodes and branches visited previously, so that we can go back to the nearest knot that contained a path still unexplored in the case that the Research in the current branch has resulted in inconsistent results or that they have not fulfilled the constraints.
 

The tree structure looks this way; Each knot corresponds to an island, and each branch represents the possible choice that can be undertaken in moving from one island to another; 
For example, in the image in question, the first node represents the capital: 
From the capital we can move in different directions (branches linking to another node): For example, we choose to move In another randomly chosen island.
On each iteration, we could move N-1 Directions (where N = number of islands): We could move in the third, or the fourth for example, provided that these islands have not already been taken into account before arriving at that currently in analysis; Each of them It will lead to several other series of discrete choices, and so on, until an optimum solution of the problem (If it exists) was found.
The green arrow represents the "descend" in the increasingly dense tree of solutions; If the conditions of the constraints have been complied with, then the arrow continues to descend; Otherwise it goes back to looking for a better solution that can satisfy the constraints. 
In this case, the X represent the unfulfilled constraints (that is, the distance currently found greater than that of the greedy distance found with the technique of the nearest neighbor for example, our constraint), where then it will go up in the decision tree to Seek a better one; While the V Represents The solution found through the whole series of discrete choices that led to the resolution Correct of the problem.

# Complexity and Problems NP
The backtracking algorithm has an exponential complexity, and the search for the optimal path in the problem of the sovereign traveler is a problem That belongs to the class of problems Np.
The Problem class Np, It consists of all those problems that are "verifiable" in polynomial time: For example, if we were told to certify that One of the solutions belonging to a problem Np Is correct, this could be verified in polynomial time.
The issues Np are solvable by applying an algorithm that "Check The correctness of an optimum solution using a number of polynomial operations In the length of the input.


# Greedy VS. Np.

In the case of a Euclidean graph (with each island far less than 150km from each other), with Few knots Evenly distributed, the path Sub-optimal Given by the procedure of the Neighbour Nearest would not exceed On average that Optimal More than the 20. 
In the output of the solution of our program, we will compare the two solutions, calculated respectively by the method of the Nearest neighbor and the Backtracking, Making it an average of performance increase.

# Acquisition of the data.

For the creation of our realm, we will benefit from the function Input file From our program.       
The file in question from which we will take all the necessary information to build the realm of Grafa-Nui, must be Located in the project folder, and will have to have a very precise structure:
 

In the first line, there will have to be the Number of islands, Excluding that of the capital (which will be created automatically by the program) and in each line to follow, land Cartesian coordinates of each island expressed in terms of PX, y), Separate From a space Between them.
Below, here is how the two examples presented in the presentation of the problem of the traveler sovereign at the beginning of the paragraph of the second question:

                                      
In the first staff we will have the total number of islands, excluding the capital;
In the following Righi we will have many coordinates (posed in the form of PX, y)) as the number of total islands in the first staff is equivalent.
The program will accept as the name of the input file only "Coordinates": In case this file is not found, the program will not produce any output About solving the problem, but will prompt you to insert the file in the correct path.

# Data Output.

If the program finds the input file, it will proceed to calculate theTo solution to the question with the two different resolution techniques, that Nearest neighbor and the Backtracking, Reporting the solution information obtained on a specially created Output. txt file in the program's root folder. The program, once the output file has been created, will then print the results on the screen. 


The output file produced by the program will be explained in this form: 

 

Where:
	Optimal Sub-path: path obtained with the procedure of the Neighbour Nearest
	Distance obtained by the procedure of the Neighbour Nearest
	Optimal path: Path obtained with the backtracking technique
	Distance obtained by backtracking technique
	Greedy Path/Optimal path: Average of the increment between the two distances.
