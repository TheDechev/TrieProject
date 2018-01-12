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

	trieNode* next;
	KeyType key; // name
	DataType data; // num
	trieNode* siblings[SIZE] = { NULL };
	char nextKey = '0';
public:
	trieNode* getNext() { return next; };
	DataType getData() { return data; }
	KeyType getKey() { return key;}
	trieNode* getSibling(int index) { return siblings[index]; }
	void setSibling(int index, trieNode* node) { siblings[index] = node; }
	char getNextKey() { return nextKey; }
	void setData(DataType _data) { data = _data; }
	void setKey(KeyType _key, char _nextKey) { key = _key; nextKey = _nextKey; }
	void DeleteNode();


};

#endif _trieNode_H