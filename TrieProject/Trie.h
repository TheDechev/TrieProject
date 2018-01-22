/*
Data structure
Programming exrecise
Trie ADT
Martin Dechev - ID 302266911
Eran Atia	  - ID 204122055
*/

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
	Trie() { root = new trieNode; }
	~Trie() { this->MakeEmpty();  delete root; }
	void MakeEmpty();
	bool isEmpty();
	DataType Find(KeyType key);
	void Insert(KeyType key, DataType data=0);
	void Delete(KeyType key);
	KeyType approxFind(KeyType &Str);
	void printTree();
	void fixWord(KeyType& key);
	void oneWordAtATime(KeyType& original, KeyType& newWord);
};

#endif