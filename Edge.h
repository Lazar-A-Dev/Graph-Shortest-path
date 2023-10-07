#pragma once
#include<iostream>
using namespace std;
class LinkedNode;
class Edge {
public:
	LinkedNode* dest;
	Edge* link;
	int weight;


public:

	Edge() {
		dest = NULL;
		link = NULL;
		weight = 0;
	}

	Edge(Edge* link, LinkedNode* dest, int weight) {
		this->link = link;
		this->dest = dest;
		this->weight = weight;
	}
};