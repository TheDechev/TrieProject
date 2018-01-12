#include "trieNode.h"

void trieNode::DeleteNode()
{
	trieNode* temp = this;
	char ch = this->getNextKey();
	while (ch != '\0') {
		temp = temp->next;
		ch = temp->getNextKey();
	}
	for (int i = 0; i < SIZE; i++) {
		temp = this->getSibling[i];
		if(temp)
			temp->DeleteNode();
	}

	delete this;
}


