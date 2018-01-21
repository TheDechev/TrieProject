#include "trieNode.h"

int trieNode::DeleteNode(KeyType key)
{
	trieNode* current;
	int check,whichKey, index, childrenStatus;
	index = this->compareKeys(key,whichKey);
	
	if (key[0] == '\0')
		return DONT_DELETE;

	if (whichKey == EQUAL) {

		childrenStatus = this->hasChildren();
		if (!childrenStatus) // has no children
		{//
			delete this;
			return DELETE_NODE;
		}
		else {
			if (this->getData() > 0) // found a sub word 
				this->resetData();
			else 
			{
				return DONT_DELETE;
			}

		}
	}
	else if (whichKey == OLD_KEY) 
	{
		current = this->getChild(key[index] - 'a');
		if (!current) { // has no relevant child
			return DONT_DELETE;
		}
		else {
			check=current->DeleteNode(key.substr(index));
			if (check == DELETE_NODE)
				this->setChild(key[index] - 'a', NULL);
			if (!(current->hasChildren()) && current->getData() == 0) {
				delete this;
				return DELETE_NODE;
			}
		}
	}
	else {
		return DONT_DELETE;
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

void trieNode::updateNode(KeyType key)
{	
	int index, whichKey;
	trieNode* current, *nodeNew, *nodeOld;
	KeyType endKeyOld, endKeyNew, beginKeyOld;
	index = this->compareKeys(key, whichKey);
	endKeyNew = key.substr(index);
	if (whichKey == EQUAL) {
		this->increaseData();
	}

	else if (whichKey == OLD_KEY) {
		current = this->getChild(key[index] - 'a');
		if (current) {
			current->updateNode(key.substr(index));
		}
		else {
			this->setChild(key[index] - 'a', createNode(key, index));
			this->getChild(key[index] - 'a')->increaseData();
		}
	}

	else if(whichKey==NEW_KEY) // the new key is smaller and has ended
	{
		endKeyOld = this->getKey().substr(index);
		this->setKey(key);
		nodeOld = createNode(endKeyOld, 0);
		nodeOld->setData(this->getData());
		this->setData(1);
		this->mergeChildren(nodeOld);
		this->setChild(endKeyOld[0] - 'a', nodeOld);


	}
	else  // both keys haven't ended and have simillar start
	{

		endKeyOld = this->getKey().substr(index);
		beginKeyOld = this->getKey().substr(0, index);
		this->setKey(beginKeyOld);
		nodeOld = createNode(endKeyOld, 0);
		nodeOld->setData(this->getData());
		nodeNew = createNode(endKeyNew, 0);
		nodeNew->increaseData();
		this->resetData();
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
		cout << previous <<" appears: " << this->getData() << endl;
	}

	for (int i = 0; i < SIZE; i++) {
		current = this->getChild(i);
		if (current) {
			this->getChild(i)->printNode(previous);
		}
			
	}
}

KeyType trieNode::approxFindRec(KeyType& Str,bool& isData)
{
	KeyType previous, check, temp;
	trieNode* current = this;
	int whichKey, index;
	index = current->compareKeys(Str, whichKey);
	previous = current->getKey();

	if (whichKey == trieNode::EQUAL) {

		if (current->getData() == 0){
			findFirstSon(current, previous);
			return previous;
		}

		else {
			isData = true;
			current->setData(current->getData() - 1);
			return to_string(current->getData());
		}
	}

	else if (whichKey == trieNode::OLD_KEY)
	{
		if (current->getChild(Str[index] - 'a'))
		{
			temp = Str.substr(index);
			check=current->getChild(Str[index] - 'a')->approxFindRec(temp,isData);
			
			if (isData)
				return check;
			else
				return previous + check;
		}
		else { // after the prefix has  different 
			findFirstSon(current, previous);
			return previous;
		}

	}

	else if (whichKey == trieNode::NEW_KEY) // the new key is smaller and has ended
	{
		findFirstSon(current, previous);
		return previous;
	}
	else  // both keys haven't ended and have simillar start
	{
		findFirstSon(current, previous);
		return previous;
	}
	return "0";
}

void trieNode::findFirstSon(trieNode * current, KeyType & previous)
{
	bool flag = 0;
	while (current->getData() == 0) {
		for (int i = 0; i < SIZE; i++) {
			if (current->getChild(i)) {
				flag = 1;
				current = current->getChild(i);
				previous += current->getKey();
				break;
			}
		}
		if(flag==0)
			previous = WORD_NOT_FOUND;

	}


}

DataType trieNode::findRec(KeyType key)
{
	int whichKey, index;

	index=this->compareKeys(key, whichKey);

	if (whichKey == trieNode::EQUAL) {
		return 	this->getData();
	}
	else if (whichKey == trieNode::OLD_KEY)
	{
		if (this->getChild(key[index] - 'a')) {
			return this->getChild(key[index] - 'a')->findRec(key.substr(index));
		}
		else {
			return NOT_FOUND;
		}
		
	}

	else 
	{
		return NOT_FOUND;
	}

}

void trieNode::makeEmptyRec()
{
	trieNode* current;

	for (int i = 0; i < SIZE; i++) {
		current = this->getChild(i);
		if (current) {
			current->makeEmptyRec();
			delete current;
			this->setChild(i, NULL);
		}
	}
}






