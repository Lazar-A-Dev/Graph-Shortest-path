#include<iostream>
#include"Graph.h"
using namespace std;
void main() {
	Graph g;
	g.InsertNode(1);
	g.InsertNode(2);
	g.InsertNode(3);
	g.InsertNode(4);
	g.InsertNode(5);
	g.InsertNode(6);
	g.InsertNode(7);
	g.InsertNode(8);

	g.InsertDoubleEdge(1, 2, 3);
	g.InsertDoubleEdge(1, 3, 1);
	g.InsertDoubleEdge(2, 4, 3);
	g.InsertDoubleEdge(2, 5, 2);
	g.InsertDoubleEdge(3, 6, 2);
	g.InsertDoubleEdge(4, 7, 4);
	g.InsertDoubleEdge(5, 6, 2);
	g.InsertDoubleEdge(5, 3, 10);
	g.InsertDoubleEdge(5, 8, 1);
	g.InsertDoubleEdge(6, 8, 6);
	g.InsertDoubleEdge(7, 8, 5);

	//g.DeleteNode(1);
	//g.DeleteNode(5);
	//g.InsertEdge();
	//g.InsertEdge();
	//g.InsertEdge();
	//g.BFS();
	//g.DFS();
	g.ShortestPath(1);
	//cout << "Broj obidjenih cvorova: " << g.ReachableInNHoops(g.start, 3) << endl;
	//cout << "Cvor sa najvise potega: " << g.GetTownName() << endl;
	g.PrintGraph();
	system("pause");
}