#include "Graph.h"

Graph::Graph() {
	vertices = 0;
	namedVertices = 0;
	adjMatrix = nullptr;
	pageRanks = nullptr;
	outgoins = nullptr;
}

Graph::Graph(int v) {
	vertices = v;
	namedVertices = 0;
	pageRanks = new double[vertices];
	outgoins = new int[vertices];
	adjMatrix = new int*[vertices];
	for (int i = 0; i < vertices; i++) {
		pageRanks[i] = 1 / static_cast<double>(vertices);
		outgoins[i] = 0;
		adjMatrix[i] = new int[vertices];
		for (int j = 0; j < vertices; j++) {
			adjMatrix[i][j] = 0;
		}
	}
}

void Graph::addVertex(string s) {
	names[s] = namedVertices;
	reverse_names[namedVertices] = s;
	namedVertices++;
}


void Graph::addEdge(string p1, string p2) {
	int src = names[p1];
	int dest = names[p2];

	adjMatrix[src][dest] = 1;
}

int Graph::getVertexIndex(string s) {
	return names[s];
}

double Graph::getVertexPR(string s) {
	return pageRanks[names[s]];
}


void Graph::printMatrix() {
	for (int i = 0; i < vertices; i++) {

		for (int j = 0; j < vertices; j++) {
			cout << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Graph::calcOutgo() {
	for (int i = 0; i < vertices; i++) {
		int sum = 0;
		for (int j = 0; j < vertices; j++) {
			sum += adjMatrix[i][j];
		}
		outgoins[i] = sum;
	}
}


void Graph::calcPageRank() {
	double term1 = (0.15) / static_cast<double>(vertices);
	double* newPageranks = new double[vertices];
	adjustAdj();
	for (size_t i = 0; i < vertices; i++) {
		double term2 = 0;
		//cout << i << endl;
		for (size_t j = 0; j < vertices; j++)
		{
			if (adjMatrix[j][i] == 1 && i != j) {
				//cout << pageRanks[j] << " " << outgoins[j] << endl;
				term2 += pageRanks[j] / outgoins[j];
			}
		}
		//cout << endl;
		newPageranks[i] = term1 + 0.85 * term2;
	}

	pageRanks = newPageranks;
}

void Graph::printPageRanks() {
	for (int i = 0; i < vertices; i++) {
		cout << pageRanks[i] << " ";
	}
}

void Graph::adjustAdj() {
	for (int i = 0; i < vertices; i++) {
		if (outgoins[i] == 0) {
			for (int j = 0; j < vertices; j++) {
				adjMatrix[i][j] = 1;
			}
			outgoins[i] = vertices-1;
		}

	}
}

void Graph::writePageRank(string s)
{
	fstream fout;

	fout.open(s, ios::out | ios::app);

	
	for (int i = 0; i < vertices; i++) {

		fout << reverse_names[i] << ","
			<< pageRanks[i] << "\n";
	}
}

void Graph::readPageRank(string s) {
	fstream fin;

	fin.open(s, ios::in);

	vector<string> row;
	string line, word, temp;

	while (fin >> temp) {

		row.clear();


		getline(fin, line);

		stringstream s(temp);

		while (getline(s, word, ',')) {

			row.push_back(word);
		}

		pageRanks[names[row.at(0)]] = stof(row.at(1));



	}

}
