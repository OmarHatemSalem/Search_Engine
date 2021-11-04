#ifndef GRAPH_H
#define GRAPH_H 

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>


using namespace std;

class Graph
{
	int vertices;
	int** adjMatrix;
	double* pageRanks;
	double* impressions;
	double* clicks;
	double* CTRs;
	double* scores;
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
	double getScore(string s);

	void setImpressions(double imps, string s);
	void incrementImps(string s);
	void setClicks(double cls, string s);

	void calcOutgo();
	void calcPageRank();
	void calcCTR(string s);
	void calcScore(string s);

	void printMatrix();
	void printPageRanks();
	void printImpressions();
	void printClicks();
	void printCTRs();
	void printScores();

	void adjustAdj();
	void writePageRank(string s);
	void readPageRank(string s);

	void writeImpressions(string s);
	void readImpressions(string s);

	void writeClicks(string s);
	void readClicks(string s);

	void writeCTRs(string s);
	void readCTRs(string s);
};

#endif