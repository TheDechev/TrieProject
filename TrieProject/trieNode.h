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
public:
	enum { EQUAL, NEW_KEY, OLD_KEY, BOTH_KEYS, NOT_FOUND=-1, DELETE_NODE=-2, DONT_DELETE=-3};
	trieNode() { data = 0; }
	~trieNode() { }
	DataType getData() { return data; }
	KeyType getKey() { return key;}
	void setKey(KeyType _key) { key = _key; }
	trieNode* getChild(int index) { return children[index]; }
	void setChild(int index, trieNode* node) { children[index] = node; }
	void increaseData() { data++; }
	int DeleteNode(KeyType key);
	int compareKeys(KeyType newKey, int& whichKey);
	void updateNode(KeyType key); 
	trieNode* createNode(KeyType _key, int startIndex);
	void mergeChildren(trieNode* node);
	void resetData() { data = 0; }
	bool hasChildren();
	void printNode(string previous);
	void setData(int newData) { data = newData;}
	KeyType approxFindRec(KeyType& Str, bool& isData);
	void findFirstSon(trieNode* current, KeyType& previous);
	DataType findRec(KeyType key);
	void makeEmptyRec();

};

#endif 