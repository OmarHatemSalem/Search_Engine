#ifndef PAGE_H
#define PAGE_H 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>


using namespace std;

struct vertex {
	int index;
	string name;
	
};

class Page
{
	vertex node;
	double pageRank;
	vector<string> keywords;
	static int totalPages;
	double impressions;
	double clicks;
	double CTR;
	double score;

public:
	Page();
	Page(string s);
	void setVertex(int v);

	vertex getVertex();

	void setImpress(double x);

	void printTitle();
	void printPage();

	void getPageRank(double data);

	void incrementClicks();
	void incrementImps();
	void recalcCTR();

	double getScore();
	void recalcScore();

	bool operator>(Page B);
	bool operator>=(Page B);
	bool operator<(Page B);
	bool operator<=(Page B);
	bool operator==(Page B);

};

#endif