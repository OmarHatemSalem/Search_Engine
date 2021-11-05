#include "Trie.h"
#include "Graph.h"

using namespace std;

const int WEBS = 4;
const int LINKS = 4;


void read_keywords(Trie& tree, Graph& web);
void read_links(Graph& web);
void queryParser(string q, Trie& tree, Graph& web);



bool sortbysec(const pair<string, double>& a, const pair<string, double>& b);

int main() {


	Trie keys;
	Graph web(WEBS);

	read_keywords(keys, web);
	read_links(web);
	web.readPageRank("pageranks.csv");
	web.readImpressions("impressions.csv");


	for (size_t i = 0; i < 1; i++)
	{
		web.calcPageRank();
	}
	web.writePageRank("pageranks.csv");

	queryParser("data AND structures", keys, web);
	cout << endl;
	/*string enter;
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
				cin >> search_choice;

				char webpage_choice;

			} while (search_choice != '3');
			//system("cls");
		}

	} while (enter != "2");*/
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

void read_keywords(Trie& tree, Graph& web)
{


	fstream fin;

	fin.open("keywords.csv", ios::in);

	vector<string> row;
	string line, word, temp;

	while (fin >> temp) {

		row.clear();

		getline(fin, line);

		stringstream s(temp);

		while (getline(s, word, ',')) {

			row.push_back(word);
		}


		web.addVertex(row.at(0));
		for (unsigned i = 1; i < row.size(); i++) {
			tree.insert_with_Web(row.at(i), row.at(0));
		}

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
			vector<pair<string, double>> webScores;
			for (unsigned i = 0; i < result->websites.size(); i++) {
				web.calcScore(result->websites.at(i));
				pair<string, double> candidate = { result->websites.at(i), web.getScore(result->websites.at(i)) };
				webScores.push_back(candidate);
			}
			sort(webScores.rbegin(), webScores.rend(), sortbysec);

			cout << "Search Results for: " << q << endl;
			for (unsigned i = 0; i < result->websites.size(); i++) {
				web.incrementImps(result->websites.at(i));
				web.calcScore(result->websites.at(i));
				cout << webScores.at(i).first << " " << webScores.at(i).second << endl;
			}
		}
	}
	else if (row.size() == 3) {
		auto result1 = tree.search_return(row.at(0));
		auto result2 = tree.search_return(row.at(2));

		if ((result1 == nullptr || result2 == nullptr) && row.at(1) == "AND") {
			cout << "No websites contain the query \"" << q << "\"" << endl;
		}
		else if ((result1 == nullptr || result2 == nullptr) && row.at(1) == "OR") {
			cout << "No websites contain the query \"" << row.at(2) << "\"" << endl;
		}
		else {

			set<pair<string, double>> webScores1;
			for (unsigned i = 0; i < result1->websites.size(); i++) {
				web.calcScore(result1->websites.at(i));
				pair<string, double> candidate = { result1->websites.at(i), web.getScore(result1->websites.at(i)) };
				webScores1.insert(candidate);
			}

			set<pair<string, double>> webScores2;
			for (unsigned i = 0; i < result2->websites.size(); i++) {
				web.calcScore(result2->websites.at(i));
				pair<string, double> candidate = { result2->websites.at(i), web.getScore(result2->websites.at(i)) };
				webScores2.insert(candidate);
			}




			if (row.at(1) == "AND") {


				vector<pair<string, double>> v3;

				set_intersection(webScores1.begin(), webScores1.end(),
					webScores2.begin(), webScores2.end(),
					back_inserter(v3));

				cout << "Search Results for: " << q << endl;
				for (int i = v3.size() - 1; i >= 0; i--) {
					web.incrementImps(v3.at(i).first);
					web.calcScore(v3.at(i).first);
					cout << v3.at(i).first << " " << v3.at(i).second << endl;
				}

				/*for (unsigned i = 0; i < result1->websites.size(); i++) {
					cout << webScores1.at(i).first << " " << webScores1.at(i).second << endl;
				}

				for (unsigned i = 0; i < result2->websites.size(); i++) {
					cout << webScores2.at(i).first << " " << webScores2.at(i).second << endl;
				}*/

			}
			else if (row.at(1) == "OR") {
				vector<pair<string, double>> v3;

				set_union(webScores1.begin(), webScores1.end(),
					webScores2.begin(), webScores2.end(),
					back_inserter(v3));

				cout << "Search Results for: " << q << endl;
				for (int i = v3.size() - 1; i >= 0; i--) {
					web.incrementImps(v3.at(i).first);
					web.calcScore(v3.at(i).first);
					cout << v3.at(i).first << " " << v3.at(i).second << endl;
				}
			}
		}
	}
}



bool sortbysec(const pair<string, double>& a, const pair<string, double>& b)
{
	return (a.second < b.second);
}