#include "Trie.h"

void Trie::MakeEmpty()
{
	trieNode* temp;
	char ch;
	if (root) {
		root->DeleteNode();
	}

}

bool Trie::isEmpty()
{
	if (root)
		return true;
	return false;
}

void Trie::Insert(KeyType key, DataType data)
{
	trieNode* node, *temp = root;
	int index = 0;
	while (key[index] != '\0') {

		if (temp->getSibling[key[0] - '0']) //check if existts
		{

		}
		else
		{
			node = new trieNode;
			temp->setSibling[index] = node;
			temp->setKey(key,key[index+1]);
			temp = node->getNext();

			

		}
		index++;
	}


}
