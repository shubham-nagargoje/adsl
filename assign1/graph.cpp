/*
 * graph.cpp
 *
 *  Created on: 24-Feb-2018
 *      Author: shubham
 */
/*There are flight paths between cities. If there is a flight between city A and city
 B then there is an edge between the cities. The cost of the edge can be the time
 that flight take to reach city B from A, or the amount of fuel used for the
 journey. Represent this as a graph. The node can be represented by airport
 name or name of the city. Use adjacency list representation of the graph or use
 adjacency matrix representation of the graph. Justify the storage
 representation used.*/

#include<iostream>

using namespace std;

class Graph {
	int V, E;
	int **Adj;
	string *s;
public:
	void CreateGraph(Graph *);
	void Display(Graph *);
};

void Graph::CreateGraph(Graph *G) {
	cout << "Enter the number of cities\n";
	cin >> G->V;

	Adj = new int *[G->V];
	for (int i = 0; i < G->V; i++)
		Adj[i] = new int[G->V];

	s = new string[G->V];
	for (int i = 0; i < G->V; i++) {
		cout << "Enter the name of the city" << endl;
		cin >> s[i];
	}

	for (int u = 0; u < G->V; u++)
		for (int v = 0; v <= u; v++) {
			if (u == v) {
				Adj[u][v] = 0;
				break;
			}
			cout << "Is there flight between " << s[u] << " and " << s[v]
					<< endl;
			char ch;
			cin >> ch;
			int cost = 0;
			if (ch == 'y') {
				cout << "Enter the cost";
				cin >> cost;
				Adj[u][v] = Adj[v][u] = cost;
				E++;
			} else
				Adj[u][v] = Adj[v][u] = cost;
		}
}

void Graph::Display(Graph *G) {
	for (int u = 0; u < G->V; u++)
		for (int v = 0; v <= u; v++) {
			cout << "connecting flight " << s[u] << " and " << s[v] << " Cost: "
					<< Adj[u][v] << endl;
		}
}

int main() {
	Graph G;
	G.CreateGraph(&G);
	G.Display(&G);

	return 0;
}

