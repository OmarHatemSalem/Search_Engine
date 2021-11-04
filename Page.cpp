#include "Page.h"

int Page::totalPages = 1;


Page::Page() {
	node.name = to_string(totalPages);
	node.index = totalPages;
	totalPages++;
	impressions = 0;
	clicks = 0;
	score = 0;
	CTR = 0;
}

Page::Page(string s) {
	node.name = s;
	node.index = totalPages;
	totalPages++;
	impressions = 0;
	clicks = 0;
	CTR = 0;
	score = 0;

}

void Page::setVertex(int v) {
	if (v < totalPages)
		node.index = v;
}

void Page::printTitle() {
	cout << node.name;
}

vertex Page::getVertex() {
	return node;
}

void Page::setImpress(double x) {
	if (x >= 0)
		impressions = x;
}

void Page::printPage() {
	cout << node.name << endl;
	cout << pageRank << " " << impressions << " " << CTR << " " << score << endl;
}

void Page::getPageRank(double data) {
	pageRank = data;
}

void Page::incrementClicks() {
	clicks++;
}

void Page::incrementImps() {
	impressions++;
}

void Page::recalcCTR() {
	CTR = clicks / impressions;
}

double Page::getScore() {
	return score;
}

void Page::recalcScore() {
	recalcCTR();
	score = 0.4 * pageRank + 0.6 * (pageRank * (1 - (0.1 * impressions) / (1 + 0.1 * impressions) ) +
		CTR * ((0.1 * impressions) / (1 + 0.1 * impressions)));

}

bool Page::operator>(Page B) {
	return (score > B.getScore());
}
bool Page::operator<(Page B) {
	return !(*this > B);
}

bool Page::operator>=(Page B) {
	return (score >= B.getScore());
}
bool Page::operator<=(Page B) {
	return !(*this >= B);
}

bool Page::operator==(Page B) {
	return (node.name == B.getVertex().name);
}