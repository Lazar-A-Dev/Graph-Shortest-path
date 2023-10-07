#pragma once
#include<iostream>
#include"LinkedNode.h"
#include"Edge.h"
using namespace std;
class Graph
{
public:
	LinkedNode* start;
	int size;

public:

	Graph();
	~Graph();
	void InsertNode(int p);
	LinkedNode* FindNode(int p);
	void DeleteNode(int p);
	void InsertEdge(int a, int b, int w);
	void InsertDoubleEdge(int a, int b, int w);
	Edge* FindEdge(int a, int b);
	bool EdgeExists(int a, int b);
	bool DeleteEdge(int a, int b);
	void BFS();
	void DFS();
	int ReachableInNHoops(LinkedNode* a, int n);
	int GetTownName();
	void ShortestPath(int node);
	void PrintGraph();
};
