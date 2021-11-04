#include "Trie.h"

Trie::Trie() {
	base = getNode();
}

struct TrieNode* Trie::getNode()
{
	struct TrieNode* pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}


void Trie::insertNode(struct TrieNode* root, string key)
{
	struct TrieNode* pCrawl = root;

	for (unsigned i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	pCrawl->isEndOfWord = true;
}

void Trie::insert_with_WebNode(struct TrieNode* root, string key, string P)
{
	struct TrieNode* pCrawl = root;

	for (unsigned i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	pCrawl->isEndOfWord = true;
	pCrawl->websites.push_back(P);
}


void Trie::insert(string key) {
	insertNode(base, key);
}

void Trie::insert_with_Web(string key, string P) {
	insert_with_WebNode(base, key, P);
}

bool Trie::searchNode(struct TrieNode* root, string key)
{
	struct TrieNode* pCrawl = root;

	for (unsigned i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->isEndOfWord);
}


bool Trie::search(string key)
{
	return searchNode(base, key);
}

bool Trie::search_display_Node(struct TrieNode* root, string key) {
	struct TrieNode* pCrawl = root;

	for (unsigned i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}
	
	if (pCrawl->isEndOfWord) {
		cout << "Keyword: " << key << endl;
		for (unsigned i = 0; i < pCrawl->websites.size(); i++) {
			cout << pCrawl->websites.at(i) << endl;
		}
		cout << endl;
		return true;
	}
	else {
		return false;
	}
}

bool Trie::search_display(string key) {
	return search_display_Node(base, key);
}

struct TrieNode* Trie::search_return_Node(struct TrieNode* root, string key) {
	
	struct TrieNode* pCrawl = root;

	for (unsigned i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return nullptr;

		pCrawl = pCrawl->children[index];
	}

	if (pCrawl->isEndOfWord) {
		return pCrawl;
	}
	else {
		return nullptr;
	}
}

struct TrieNode* Trie::search_return(string key) {
	return search_return_Node(base, key);
}
