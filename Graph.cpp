#include "Graph.h"
Graph::Graph() {
	start = NULL;
	size = 0;
}

Graph::~Graph() {

}

void Graph::InsertNode(int p) {
	LinkedNode* tmp = new LinkedNode(start, NULL, p);
	start = tmp;
	size++;
}

LinkedNode* Graph::FindNode(int p) {
	LinkedNode* tmp = start;
	while (tmp != NULL && tmp->info != p)
		tmp = tmp->next;

	return tmp;
}

void Graph::DeleteNode(int p) {
	LinkedNode* p1 = FindNode(p);
	LinkedNode* tmp = start;

	while (tmp != NULL) {//Svaki ulazni poteg
		if (EdgeExists(tmp->info, p1->info))
			DeleteEdge(tmp->info, p1->info);
		else if (EdgeExists(p1->info, tmp->info))
			DeleteEdge(p1->info, tmp->info);
		tmp = tmp->next;
	}

	if (p1 == start) {
		tmp = start;
		start = start->next;
		tmp = NULL;
		delete tmp;
		size--;
	}
	else {
		tmp = start;
		while (tmp->next != p1)
			tmp = tmp->next;

		tmp->next = p1->next;
		p1 = NULL;
		delete p1;
		size--;
	}
}

void Graph::InsertEdge(int a, int b, int w) {
	LinkedNode* p1 = FindNode(a);
	LinkedNode* p2 = FindNode(b);

	Edge* ed = new Edge(p1->adj, p2, w);
	p1->adj = ed;

}

void Graph::InsertDoubleEdge(int a, int b, int w) {
	LinkedNode* p1 = FindNode(a);
	LinkedNode* p2 = FindNode(b);

	Edge* ed = new Edge(p1->adj, p2, w);
	p1->adj = ed;

	ed = new Edge(p2->adj, p1, w);
	p2->adj = ed;
}

Edge* Graph::FindEdge(int a, int b) {
	LinkedNode* p1 = FindNode(a);
	LinkedNode* p2 = FindNode(b);

	Edge* ed = p1->adj;
	while (ed != NULL && ed->dest != p2)
		ed = ed->link;

	return ed;
}

bool Graph::EdgeExists(int a, int b) {
	if (FindEdge(a, b))
		return true;
	return false;
}

bool Graph::DeleteEdge(int a, int b) {
	Edge* pot = FindEdge(a, b);
	if (pot == NULL)
		return false;

	LinkedNode* pa = FindNode(a);
	if (pot == pa->adj) {
		pa->adj = pot->link;
		delete pot;
		return true;
	}

	Edge* tpot = pa->adj;
	while (tpot->link != pot)
		tpot = tpot->link;
	tpot->link = pot->link;
	delete pot;
	return true;
}

void Graph::BFS() {
	LinkedNode** stack = new LinkedNode * [size];
	LinkedNode* p1 = start;
	p1->ChangeStatus(1);
	int indeks = 0;
	int point = 1;
	stack[indeks++] = p1;
	while (p1 != NULL && indeks < size) {
		Edge* ed = p1->adj;
		while (ed != NULL) {
			if (ed->dest->status == 0) {
				ed->dest->ChangeStatus(1);
				stack[indeks++] = ed->dest;
			}
			ed = ed->link;
		}
		p1 = stack[point++];
	}

	cout << "Nodes in BFS: ";
	for (int i = 0; i < size; i++) {
		stack[i]->ChangeStatus(0);
		cout << "[" << stack[i]->info << "] ";
	}
	cout << endl;
}

void Graph::DFS() {
	LinkedNode** stack = new LinkedNode * [size];
	LinkedNode* p1 = start;
	int indeks = 0;
	int point = 0;

	p1->ChangeStatus(1);
	stack[indeks++] = p1;
	cout << "Nodes in DFS: ";
	cout << "[" << p1->info << "] ";
	while (p1 != NULL && indeks < size) {
		//cout << "[" << point << "] = " << stack[point]->info << endl;
		Edge* ed = p1->adj;
		while (ed != NULL) {
			//cout << "Dest: " << ed->dest->info << " Status: " << ed->dest->status << endl;
			if (ed->dest->status == 0) {
				ed->dest->ChangeStatus(1);

				stack[indeks++] = ed->dest;
				if (indeks < size)
					point++;
				cout << "[" << ed->dest->info << "] ";
				break;
			}
			ed = ed->link;
		}
		if (ed == NULL) {
			stack--;
			p1 = stack[point];
		}
		else
			p1 = stack[point];
	}

	//cout << "Nodes in stack: ";
	//for (int i = 0; i < size; i++) {
		//stack[i]->ChangeStatus(0);
		//cout << "[" << stack[i]->info << "] ";
	//}
	cout << endl;
}

int Graph::ReachableInNHoops(LinkedNode* a, int n) {
	LinkedNode** stack = new LinkedNode * [size];
	LinkedNode* p = a;
	int indeks = 0;
	int point = 1;
	int count = 0;
	p->ChangeStatus(1);
	stack[indeks++] = p;
	while (p != NULL && count < n) {
		Edge* ed = p->adj;
		while (ed != NULL) {
			if (ed->dest->status == 0) {
				ed->dest->ChangeStatus(1);
				stack[indeks++] = ed->dest;
			}
			ed = ed->link;
		}
		p = stack[point++];
		count++;
	}


	return indeks;
}

int Graph::GetTownName() {
	int max = 0;
	int current = 0;
	int nameOfNode = start->info;
	LinkedNode* p = start;

	while (p != NULL) {
		Edge* ed = p->adj;
		while (ed != NULL) {
			current++;
			ed = ed->link;
		}
		if (current > max) {
			max = current;
			nameOfNode = p->info;
		}
		current = 0;
		p = p->next;
	}

	return nameOfNode;
}

void Graph::ShortestPath(int node) {
	LinkedNode** stack = new LinkedNode * [size];
	LinkedNode* p1 = start;
	p1->ChangeDistance(0);
	p1->ChangeStatus(1);
	int indeks = 0;
	int point = 1;
	stack[indeks++] = p1;

	while (p1 != NULL && point < size) {
		Edge* ed = p1->adj;
		while (ed != NULL) {
			if (ed->dest->distance > p1->distance + ed->weight) {
				ed->dest->ChangeDistance(p1->distance + ed->weight);
				LinkedNode* p2 = ed->dest;
				Edge* ed2 = p2->adj;
				while (ed2 != NULL) {
					if (ed2->dest->distance > p2->distance + ed2->weight) {
						//cout << p1->info << " -> " << ed->dest->info << endl;
						ed2->dest->ChangeDistance(p2->distance + ed2->weight);
					}
					ed2 = ed2->link;
				}
			}
			if (ed->dest->status == 0) {
				ed->dest->ChangeStatus(1);
				ed->dest->ChangePast(p1);
				stack[indeks++] = ed->dest;

			}
			ed = ed->link;
		}
		p1 = stack[point++];
	}

	cout << "Shortest path info " << endl;
	for (int i = 0; i < size; i++) {
		stack[i]->ChangeStatus(0);
		cout << "[" << stack[i]->info << "] {" << stack[i]->distance << "} " << endl;
	}
	cout << endl;
	
	cout << "The path: ";
	LinkedNode* n = FindNode(node);
	cout << "[" << n->info << "] ";
	while (n->past != NULL) {
		cout << "[" << n->past->info << "] ";
		n = n->past;
	}
	cout << endl;
}

void Graph::PrintGraph() {
	LinkedNode* tmp = start;
	while (tmp != NULL) {
		cout << "[" << tmp->info << "]";
		Edge* ed = tmp->adj;
		while (ed != NULL) {
			cout << " --{" << ed->weight << "}> " << "[" << ed->dest->info << "] |";
			ed = ed->link;
		}
		tmp = tmp->next;
		cout << endl;
	}
}