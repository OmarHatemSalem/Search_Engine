#include "Page.h"
#include "Trie.h"
#include "Graph.h"

using namespace std;

const int WEBS = 4;
const int LINKS = 4;


void read_keywords_impressions(Trie& tree, Graph& web);
void read_links(Graph& web);
void queryParser(string q, Trie& tree, Graph& web);

void heapify(struct TrieNode* p, int i);
void build_heap(struct TrieNode* p);
void heap_sort(struct TrieNode* p);

int main() {


	Trie keys;
	Graph web(WEBS);
	
	read_keywords_impressions(keys, web);
	read_links(web);

	/*cout << keys.search_display("programming") << endl;
	web.printMatrix();*/

	/*
	web.printPageRanks();
	cout << endl;
	web.readPageRank("pageranks.csv");
	web.printPageRanks();
	cout << endl;*/

	for (size_t i = 0; i < 1; i++)
	{
		web.calcPageRank();
	}
	string enter;
	do {
		cout << "Welcome!" << endl;
		cout << "1. New Search" << endl;
		cout << "2. Exit" << endl;

		cout << "Type in your choice: ";
		cin >> enter;

		if (enter == "1") {
			char search_choice='1';
			do {
				//system("cls");
				string query;
				cout << "search for: ";
				getline(cin, query);
				cout << query;
				system("pause");
				queryParser(query, keys, web);

				/*cout << "\nWould you like to: " << endl;
				cout << "1. Open a Webage" << endl;
				cout << "2. New Search" << endl;
				cout << "3. Exit" << endl;
				cin >> search_choice;*/

				char webpage_choice;
			
			} while (search_choice != '3');
			//system("cls");
		}

	} while (enter != "2");
}




void read_links(Graph& web) {
	fstream fin;

	fin.open("webGraph.csv", ios::in);

	vector<string> row;
	string line, word, temp;

	while (fin >> temp) {

		row.clear();


		getline(fin, line);

		stringstream s(temp);

		while (getline(s, word, ',')) {

			row.push_back(word);
		}

		web.addEdge(row.at(0), row.at(1));

		

	}

	web.calcOutgo();
}

void read_keywords_impressions(Trie& tree, Graph& web)
{

	vector<Page> ps;

	fstream fin;

	fin.open("impressions.csv", ios::in);

	vector<string> row;
	string line, word, temp;

	while (fin >> temp) {

		row.clear();

		getline(fin, line);

		stringstream s(temp);

		while (getline(s, word, ',')) {

			row.push_back(word);
		}

		Page website(row.at(0));
		website.setImpress(stof(row.at(1)));
		ps.push_back(website);

	}



	fin.close();

	fin.open("keywords.csv", ios::in);

	int webCount = 0;
	while (fin >> temp) {

		row.clear();

		getline(fin, line);

		stringstream s(temp);

		while (getline(s, word, ',')) {

			row.push_back(word);
		}


		web.addVertex(row.at(0));
		for (unsigned i = 1; i < row.size(); i++) {
			tree.insert_with_Web(row.at(i), ps.at(webCount));
		}

		webCount++;
	}
}

void queryParser(string q, Trie& tree, Graph& web) {
	
	vector<string> row;
	string word;
	stringstream s(q);

	while (getline(s, word, ' ')) {

		row.push_back(word);
	}

	if (row.size() == 1) {
		auto result = tree.search_return(q);

		if (result == nullptr) {
			cout << "No websites contain the query \"" << q << "\"" << endl;
		}
		else {

			for (unsigned i = 0; i < result->websites.size(); i++) {
				string name = result->websites.at(i).getVertex().name;
				result->websites[i].getPageRank(web.getVertexPR(name));
				result->websites[i].incrementImps();
				result->websites[i].recalcScore();

			}
			sort(result->websites.rbegin(), result->websites.rend());

			cout << "Search Results for: " << q << endl;
			for (unsigned i = 0; i < result->websites.size(); i++) {
				result->websites.at(i).printPage();
			}
		}
	}
	else if (row.size() == 3) {
		auto result1 = tree.search_return(row.at(0));
		auto result2 = tree.search_return(row.at(2));

		if (result1 == nullptr) {
			cout << "No websites contain the query \"" << row.at(0) << "\"" << endl;
		} else if (result2 == nullptr) {
			cout << "No websites contain the query \"" << row.at(2) << "\"" << endl;
		}
		else {

			for (unsigned i = 0; i < result1->websites.size(); i++) {
				string name = result1->websites.at(i).getVertex().name;
				result1->websites[i].getPageRank(web.getVertexPR(name));
				result1->websites[i].incrementImps();
				result1->websites[i].recalcScore();

			}

			for (unsigned i = 0; i < result2->websites.size(); i++) {
				string name = result2->websites.at(i).getVertex().name;
				result2->websites[i].getPageRank(web.getVertexPR(name));
				result2->websites[i].incrementImps();
				result2->websites[i].recalcScore();

			}
			sort(result1->websites.begin(), result1->websites.end());
			sort(result2->websites.begin(), result2->websites.end());

			if (row.at(1) == "AND") {
				vector<Page> v3;

				/*set_intersection(result1->websites.begin(), result1->websites.end(),
					result2->websites.begin(), result2->websites.end(),
					back_inserter(v3));

				cout << "Search Results for: " << q << endl;
				for (unsigned i = 0; i < v3.size(); i++) {
					v3.at(i).printPage();
				}*/

				for (unsigned i = 0; i < result1->websites.size(); i++) {
					result1->websites.at(i).printPage();
				}

				for (unsigned i = 0; i < result2->websites.size(); i++) {
					result2->websites.at(i).printPage();
				}

			} else if (row.at(1) == "OR") {
				vector<Page> v3;

				/*set_union(result1->websites.begin(), result1->websites.end(),
					result2->websites.begin(), result2->websites.end(),
					back_inserter(v3));

				cout << "Search Results for: " << q << endl;
				cout << v3.size() << endl;
				for (unsigned i = 0; i < v3.size(); i++) {
					v3.at(i).printPage();
				}*/

				for (unsigned i = 0; i < result1->websites.size(); i++) {
					result1->websites.at(i).printPage();
				}

				for (unsigned i = 0; i < result2->websites.size(); i++) {
					result2->websites.at(i).printPage();
				}

			}
		}
	}
}

void heapify(struct TrieNode* p, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < p->websites.size() && p->websites[l] > p->websites[largest])
		largest = l;

	if (r < p->websites.size() && p->websites[r] > p->websites[largest])
		largest = r;

	if (largest != i) {
		//swap(p->websites[i], p->websites[largest]);
		iter_swap(p->websites.begin() + i, p->websites.begin() + largest);

		heapify(p, largest);
	}
}

void build_heap(struct TrieNode* p)
{
	for (int i = p->websites.size() / 2 - 1; i >= 0; i--)
		heapify(p, i);
}


void heap_sort(struct TrieNode* p)
{
	build_heap(p);

	for (int i = p->websites.size() - 1; i >= 0; i--) {
		swap(p->websites[0], p->websites[i]);
		heapify(p, i);
	}
}