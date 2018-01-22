/*
Data structure
Programming exrecise
Trie ADT
Martin Dechev - ID 302266911
Eran Atia	  - ID 204122055
*/

#include "Trie.h"

// Deletes all the nodes in the tree and making it ''empty''
void Trie::MakeEmpty()
{
	if (root->hasChildren()) {
		root->makeEmptyRec();
	}
	else 
		cout << "Dictionary is empty." << endl;
}

//Checks if the Trie has any data in it
bool Trie::isEmpty()
{
	return  (root) ? true : false;
}

//Searches in the Trie for a specific key
DataType Trie::Find(KeyType key)
{
	if (root->getChild(key[0] - 'a')) 
		return root->getChild(key[0] - 'a')->findRec(key);
	else 
		return 0;
}

void Trie::Insert(KeyType key, DataType data)
{
	trieNode *current;
	char ch;
	int index = 0, whichKey = 0;
	ch = key[index];

	while(ch!='\0'){
		current = root->getChild(ch - 'a');
		if (current) // there's a child in this space
		{
			current->updateNode(key);
			break;
		}
		else {
			current = new trieNode;
			current->setKey(key);
			current->setData(current->getData()+1); // increases data by 1
			root->setChild(ch-'a', current);
			break;
		}
	}
}

//Deletes the given key from the Trie (if exists)
void Trie::Delete(KeyType key)
{
	trieNode* current = root->getChild(key[0] - 'a');

	if (!current)
		cout << "No such child to delete" << endl;
	else 
		current->DeleteNode(key);
}


/* Searches in the Trie for a given KeyType.
If the given KeyType has been found, the data = number of times it appears in the dictionary will be printed and decreased by 1.
Otherwise, it'll suggest the first alphabetical KeyType with the longest simillar prefix. */
KeyType Trie::approxFind(KeyType & Str)
{
	bool isData = 0;
	int deleteStatus;
	string check;
	if (root->getChild(Str[0] - 'a')) {
		check=root->getChild(Str[0] - 'a')->approxFindRec(Str,isData);
		if (check == "0") {
			deleteStatus = root->getChild(Str[0] - 'a')->DeleteNode(Str);
			if (deleteStatus == trieNode::DELETE_NODE)
				root->setChild(Str[0] - 'a', NULL);
		}

		if (isData) {
			cout << stoi(check) + 1<< endl;
			return WORD_FOUND;
		}
		else
			return check;
	}
	else 
		return WORD_NOT_FOUND;
}

//Prints the tree alphabeticlly
void Trie::printTree()
{
	trieNode* current;
	for (int i = 0; i < SIZE; i++) {
		current = root->getChild(i);
		if (current)
			current->printNode("");
	}
}

/*Gets a key and fixes it - lowers big letters, and deletes every other sign
Input: The key to fix
Output: The fixed key*/
void Trie::fixWord(KeyType & key)
{
	int index = 0;
	char ch = key[index];

	while (ch != '\0') {
		if (ch >= 'a' && ch <= 'z') {} // skips the small letter
		else if (ch >= 'A' && ch <= 'Z') 
			key[index] = tolower(key[index]);
		else { // a special sign
			key = key.substr(0,index) + key.substr(index + 1);
			index--;
		}
		index++;
		ch = key[index];
	}
}

/*Gets a paragraph keyType, and divides it to words. Each time the original KeyType get smaller
Input: The paragrap keyType(By ref)
		The word keyType(By ref)
Output: the word in newWord keyType*/
void Trie::oneWordAtATime(KeyType & original, KeyType & newWord)
{
	int len = original.length();
	int index = 0;
	char ch = original[index];
	while (ch != ' ' && len>0) {
		len--;
		index++;
		ch = original[index];
	}

	newWord = original.substr(0, index);

	if (len == 0)
		original = "";
	else
		original = original.substr(index + 1);
}