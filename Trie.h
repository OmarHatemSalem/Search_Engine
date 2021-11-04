#ifndef TRIE_H
#define TRIE_H

#include "Page.h"


const int ALPHABET_SIZE = 26;

struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];

	vector<Page> websites;
	bool isEndOfWord;
};


class Trie
{
	TrieNode* base;
public: 

	Trie();
	struct TrieNode* getNode();

	void insertNode(struct TrieNode* root, string key);
	void insert_with_WebNode(struct TrieNode* root, string key, Page P);

	void insert(string key);
	void insert_with_Web(string key, Page P);

	bool search(string key);
	bool search_display(string key);
	struct TrieNode* search_return(string key);

	bool searchNode(struct TrieNode* root, string key);
	bool search_display_Node(struct TrieNode* root, string key);
	struct TrieNode* search_return_Node(struct TrieNode* root, string key);


};
#endif


