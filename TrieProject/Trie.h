#ifndef _Trie_H
#define _Trie_H

#include <string>
#include <iostream>
#include "trieNode.h"
using namespace std;

typedef string KeyType;
typedef int DataType;

class Trie {
	trieNode* root;
public:
	Trie();
	~Trie();
	void MakeEmpty();
	bool isEmpty();
	trieNode* getRoot() { return root; }
	DataType Find(KeyType key);
	void Insert(KeyType key, DataType data);
	void Delete(KeyType key);
	string approxFind(string &Str);
	string prefixMatch(string &Str);

};

#endif