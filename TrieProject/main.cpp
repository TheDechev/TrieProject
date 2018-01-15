#include <iostream>
#include "Trie.h"
#include "trieNode.h"
using namespace std;



void main() {

	Trie T;
	T.Insert("avi");
	T.Insert("av");

	T.printTree();

}

