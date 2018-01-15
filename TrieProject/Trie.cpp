#include "Trie.h"

//void Trie::MakeEmpty()
//{
//	trieNode* temp;
//	char ch;
//	if (root) {
//		root->DeleteNode();
//	}
//
//}

bool Trie::isEmpty()
{
	return  (root) ? true : false;
}

void Trie::Insert(KeyType key, DataType data)
{
	trieNode* temp = root, *current;
	char ch;
	int index = 0, whichKey = 0;
	ch = key[index];
	while(ch!='\0'){
		current = temp->getChild(ch - 'a');
		if (current) // there's a child in this space
		{
			index = current->compareKeys(key, whichKey);
			current->updateNode(key, whichKey, index);
			break;
		}
		else {
			current = new trieNode;
			current->setKey(key);
			current->increaseData();
			temp->setChild(ch-'a', current);
			break;
		}
		index++;
		ch = key[index];
	}

}

void Trie::Delete(KeyType key)
{
	trieNode* current = root->getChild(key[0] - 'a');

	if (!current)
		cout << "No such child to delete" << endl;
	else 
		current->DeleteNode(key);
	
}

void Trie::printTree()
{
	trieNode* current;
	for (int i = 0; i < SIZE; i++) {
		current = root->getChild(i);
		if (current)
			current->printNode("");

	}

}
