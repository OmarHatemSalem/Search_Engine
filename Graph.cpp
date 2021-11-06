#include "Graph.h"

Graph::Graph() {
	vertices = 0;
	namedVertices = 0;
	adjMatrix = nullptr;
	pageRanks = nullptr;
	impressions = nullptr;
	clicks = nullptr;
	CTRs = nullptr;
	scores = nullptr;
	outgoins = nullptr;
}

Graph::Graph(int v) {
	vertices = v;
	namedVertices = 0;
	pageRanks = new double[vertices];
	impressions = new double[vertices];
	clicks = new double[vertices];
	CTRs = new double[vertices];
	scores = new double[vertices];
	outgoins = new int[vertices];
	adjMatrix = new int*[vertices];
	for (int i = 0; i < vertices; i++) {
		pageRanks[i] = 1 / static_cast<double>(vertices);
		impressions[i] = 0;
		clicks[i] = 0;
		CTRs[i] = 0;
		scores[i] = 0;
		outgoins[i] = 0;
		adjMatrix[i] = new int[vertices];
		for (int j = 0; j < vertices; j++) {
			adjMatrix[i][j] = 0;
		}
	}
}


Graph::Graph(int v, string s1, string s2) {
	vertices = v;
	namedVertices = 0;
	pageRanks = new double[vertices];
	impressions = new double[vertices];
	clicks = new double[vertices];
	CTRs = new double[vertices];
	scores = new double[vertices];
	outgoins = new int[vertices];
	adjMatrix = new int* [vertices];
	for (int i = 0; i < vertices; i++) {
		pageRanks[i] = 1 / static_cast<double>(vertices);
		impressions[i] = 0;
		clicks[i] = 0;
		CTRs[i] = 0;
		scores[i] = 0;
		outgoins[i] = 0;
		adjMatrix[i] = new int[vertices];
		for (int j = 0; j < vertices; j++) {
			adjMatrix[i][j] = 0;
		}
	}

	readPageRank(s1);
	readImpressions(s2);
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

double Graph::getScore(string s) {
	return scores[names[s]];
}



void Graph::printMatrix() {
	for (int i = 0; i < vertices; i++) {

		for (int j = 0; j < vertices; j++) {
			cout << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Graph::setImpressions(double imps, string s) {
	if (imps > 0)
		impressions[names[s]] = imps;
}

void Graph::incrementImps(string s) {
	impressions[names[s]]++;
}


void Graph::setClicks(double cls, string s) {
	if (cls > 0)
		impressions[names[s]] = cls;
}

void Graph::incrementClicks(string s) {
	clicks[names[s]]++;
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

void Graph::calcCTR(string s) {
	int i = names[s];
	CTRs[i] = clicks[i] / impressions[i];

}

void Graph::calcScore(string s) {
	int i = names[s];

	calcCTR(s);
	scores[i] = 0.4 * pageRanks[i] + 0.6 * (pageRanks[i] * (1 - (0.1 * impressions[i]) / (1 + 0.1 * impressions[i])) +
		CTRs[i] * ((0.1 * impressions[i]) / (1 + 0.1 * impressions[i])));

}

void Graph::printPageRanks() {
	for (int i = 0; i < vertices; i++) {
		cout << pageRanks[i] << " ";
	}
}

void Graph::printImpressions() {
	for (int i = 0; i < vertices; i++) {
		cout << impressions[i] << " ";
	}
}

void Graph::printClicks() {
	for (int i = 0; i < vertices; i++) {
		cout << clicks[i] << " ";
	}
}

void Graph::printCTRs() {
	for (int i = 0; i < vertices; i++) {
		cout << CTRs[i] << " ";
	}
}
void Graph::printScores() {
	for (int i = 0; i < vertices; i++) {
		cout << scores[i] << " ";
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

	fout.open(s, ios::out);

	
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

void Graph::writeImpressions(string s) {
	fstream fout;

	fout.open(s, ios::out);


	for (int i = 0; i < vertices; i++) {

		fout << reverse_names[i] << ","
			<< impressions[i] << "\n";
	}
}

void Graph::readImpressions(string s) {
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

		impressions[names[row.at(0)]] = stof(row.at(1));



	}

}

void Graph::writeClicks(string s) {
	fstream fout;

	fout.open(s, ios::out);


	for (int i = 0; i < vertices; i++) {

		fout << reverse_names[i] << ","
			<< clicks[i] << "\n";
	}
}
void Graph::readClicks(string s) {
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

		clicks[names[row.at(0)]] = stof(row.at(1));



	}

}

void Graph::writeCTRs(string s) {
	fstream fout;

	fout.open(s, ios::out);


	for (int i = 0; i < vertices; i++) {

		fout << reverse_names[i] << ","
			<< CTRs[i] << "\n";
	}
}
void Graph::readCTRs(string s) {
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

		CTRs[names[row.at(0)]] = stof(row.at(1));



	}

}

