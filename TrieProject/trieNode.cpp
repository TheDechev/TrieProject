#include "trieNode.h"

void trieNode::DeleteNode(KeyType key)
{
	trieNode* current;
	int whichKey, index, childrenStatus;
	index = this->compareKeys(key,whichKey);
	
	if (key[0] == '\0')
		return;

	if (whichKey == EQUAL) {

		childrenStatus = this->hasChildren();
		if (!childrenStatus) // has no children
		{
			delete this;
			return;
		}
		else {
			if (this->getData() > 0) // found a sub word 
				this->resetData();
			else 
			{
				cout << "NO SUCH CHILD TO DELETE!" << endl;
			}

		}
	}
	else if (whichKey == OLD_KEY) 
	{
		current = this->getChild(key[index] - 'a');
		if (!current) { // has no relevant child
			cout << "NO SUCH CHILD TO DELETE!" << endl;
			return;
		}
		else {
			current->DeleteNode(key.substr(index));
			if (!(current->hasChildren()) && current->getData() == 0) {
				delete this;
			}
		}
	}
	else if (whichKey == NEW_KEY) // the new key is smaller and has ended
	{
		cout << "NO SUCH CHILD TO DELETE!" << endl;
	}
	else  // both keys haven't ended and have simillar start
	{
		cout << "NO SUCH CHILD TO DELETE!" << endl;
	}

}

int trieNode::compareKeys(KeyType newKey, int& whichKey)
{
	int index=0;
	while (newKey[index] != '\0' && this->getKey()[index] != '\0') {
		if (newKey[index] == this->getKey()[index])
			index++;
		else
			break;
	}


	if (newKey[index] == '\0' && this->getKey()[index] == '\0') //keys are equal
	{
		whichKey = EQUAL;
	}
	
	else if (newKey[index] == '\0') 
	{
		whichKey = 1;
	}
	else if(this->getKey()[index] == '\0') // original key 
	{
		whichKey = OLD_KEY;
	}
	else {
		whichKey = BOTH_KEYS;
	}
	return index;
}

void trieNode::updateNode(KeyType newKey, int whichKey, int index)
{	
	int newWhich, newIndex;
	trieNode* current, *nodeNew, *nodeOld;
	KeyType beginKeyOld, endKeyOld, endKeyNew = newKey.substr(index);

	if (whichKey == EQUAL) {
		this->increaseData();
	}
	else if (whichKey == OLD_KEY) {
		current = this->getChild(newKey[index] - 'a');
		if (current == NULL) {
			this->setChild(newKey[index] - 'a', createNode(newKey, index));
			this->getChild(newKey[index]-'a')->increaseData();
		}
		else {
			newIndex=current->compareKeys(endKeyNew, newWhich);
			current->updateNode(endKeyNew, newWhich, newIndex);
		}
	}
	else if(whichKey==NEW_KEY) // the new key is smaller and has ended
	{
		endKeyOld = this->getKey().substr(index);
		this->setKey(newKey);
		this->increaseData();
		nodeOld = createNode(endKeyOld, 0);
		// merge the sons 
		this->setChild(endKeyOld[0] - 'a', nodeOld);


	}
	else  // both keys haven't ended and have simillar start
	{
		endKeyOld = this->getKey().substr(index);
		beginKeyOld = this->getKey().substr(0, index-1);
		this->setKey(beginKeyOld);
		nodeOld = createNode(endKeyOld, 0);
		nodeNew = createNode(endKeyNew, 0);
		this->mergeChildren(nodeOld);
		this->setChild(endKeyOld[0] - 'a', nodeOld);
		this->setChild(endKeyNew[0] - 'a', nodeNew);
	}
}

trieNode* trieNode::createNode(KeyType _key, int startIndex)
{
	trieNode* node = new trieNode;
	node->setKey(_key.substr(startIndex));
	return node;
}

void trieNode::mergeChildren(trieNode* node)
{
	trieNode* current;
	for (int i = 0; i < SIZE; i++) {
		current = this->getChild(i);
		if (current) {
			node->setChild(i, current);
			this->setChild(i, NULL);
		}
	}
}

bool trieNode::hasChildren()
{
	for (int i = 0; i < SIZE; i++) {
		if (this->getChild(i)) 
			return true; // a child has been found
	}
	return false;
}

void trieNode::printNode(string previous)
{
	trieNode* current;
	previous += this->getKey();
	if (this->getData() != 0) {
		cout << previous <<" appears :" << this->getData() << endl;
	}

	for (int i = 0; i < SIZE; i++) {
		current = this->getChild(i);
		if (current) {
			this->getChild(i)->printNode(previous);
		}
			
	}
}






