#ifndef GRAPH_H
#define GRAPH_H 

#include "Page.h"

class Graph
{
	int vertices;
	int** adjMatrix;
	double* pageRanks;
	int* outgoins;
	int namedVertices;
	unordered_map<string, int> names;
	unordered_map<int, string> reverse_names;

public:
	Graph();
	Graph(int v);

	void addVertex(string s);
	void addEdge(string p1, string p2);

	int getVertexIndex(string s);
	double getVertexPR(string s);

	void calcOutgo();
	void calcPageRank();

	void printMatrix();
	void printPageRanks();

	void adjustAdj();
	void writePageRank(string s);
	void readPageRank(string s);
};

#endif