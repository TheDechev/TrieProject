#ifndef _trieNode_H
#define _trieNode_H

#include <string>
#include <iostream>
using namespace std;

typedef string KeyType;
typedef int DataType;

#define SIZE 26
class trieNode {

private:
	KeyType key; // name
	DataType data; // num
	trieNode* children[SIZE] = { NULL };
public:
	enum { EQUAL, NEW_KEY, OLD_KEY, BOTH_KEYS };
	trieNode() { data = 0; }
	DataType getData() { return data; }
	KeyType getKey() { return key;}
	void setKey(KeyType _key) { key = _key; }
	trieNode* getChild(int index) { return children[index]; }
	void setChild(int index, trieNode* node) { children[index] = node; }
	void increaseData() { data++; }
	void DeleteNode(KeyType key);
	int compareKeys(KeyType newKey, int& whichKey);
	void updateNode(KeyType newKey, int whichKey, int index);
	trieNode* createNode(KeyType _key, int startIndex);
	void mergeChildren(trieNode* node);
	void resetData() { data = 0; }
	bool hasChildren();
	void printNode(string previous);


};

#endif _trieNode_H