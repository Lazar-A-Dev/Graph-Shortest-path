#pragma once
#include<iostream>
using namespace std;
class Edge;
class LinkedNode {
public:
	LinkedNode* next;
	Edge* adj;
	int info;
	int status;
	int distance;
	LinkedNode* past;

public:

	LinkedNode() {
		next = NULL;
		past = NULL;
		adj = NULL;
		info = 0;
		status = 0;
		distance = 10000;
	}

	LinkedNode(LinkedNode* next, Edge* adj, int info) {
		this->next = next;
		this->adj = adj;
		this->info = info;
		this->past = NULL;
		status = 0;
		distance = 10000;
	}

	void ChangeStatus(int s) {
		this->status = s;
	}

	void ChangeDistance(int d) {
		this->distance = d;
	}

	void ChangePast(LinkedNode* p) {
		this->past = p;
	}
};