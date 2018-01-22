/*
Data structure
Programming exrecise
Trie ADT
Martin Dechev - ID 302266911
Eran Atia	  - ID 204122055
*/

#ifndef _trieNode_H
#define _trieNode_H

#include <string>
#include <iostream>
using namespace std;

typedef string KeyType;
typedef int DataType;

#define WORD_NOT_FOUND "No such prefix available"
#define WORD_FOUND "The word has been found"
#define SIZE 26

class trieNode {

private:
	KeyType key; // name
	DataType data; // num
	trieNode* children[SIZE] = { NULL };

	int compareKeys(KeyType newKey, int& whichKey) const;
	trieNode* createNode(KeyType _key, int startIndex);
	void mergeChildren(trieNode* node);
	void findFirstSon(trieNode* current, KeyType& previous);

public:
	enum { EQUAL, NEW_KEY, OLD_KEY, BOTH_KEYS, NOT_FOUND=-1, DELETE_NODE=-2, DONT_DELETE=-3};
	trieNode() { data = 0; }
	~trieNode() { }
	DataType getData() const { return data; }
	void setData(int newData) { data = newData; }
	KeyType getKey() const { return key;}
	void setKey(KeyType _key) { key = _key; }
	trieNode* getChild(int index) const { return children[index]; }
	void setChild(int index, trieNode* node) { children[index] = node; }

	int DeleteNode(KeyType key);
	void updateNode(KeyType key); 
	bool hasChildren() const;
	void printNode(string previous) const;
	KeyType approxFindRec(KeyType& Str, bool& isData);
	DataType findRec(KeyType key);
	void makeEmptyRec();
};

#endif 