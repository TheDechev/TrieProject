/* In this implementation of the Trie data structure each node contains the largest string possible.
So that if there are two words with a similar prefix, the prefix will be stored in a node , and the different postfixes will be
inserted inside the array of trieNodes that is stored in the similar prefix node.
(The first letter of each postfix represents the cell in the array)
For example: Avi and Avraham - ''Av'' is the longest prefix, so it'll be stored in the first node, and ''i'' ,'' raham''  will be nodes inside the trieNode array of Av. 
(i -> index 8, raham -> index 17)

Data structure
Programming exrecise
Trie ADT
Martin Dechev - ID 302266911
Eran Atia	  - ID 204122055
*/

#include <iostream>
#include "Trie.h"
#include "trieNode.h"
using namespace std;

int main() {

	Trie T;
	KeyType user_Input,currentWord = "";


	//Scan for the first paragraph
	while (currentWord !=".") {
		getline(cin, user_Input);
		while (user_Input != "") {
			T.oneWordAtATime(user_Input, currentWord);
			if (currentWord == ".")
				break;
			else {
				T.fixWord(currentWord);
				T.Insert(currentWord);
			}
		}
	}
	
	currentWord = "";

	//Scan for the second paragraph
	while (currentWord != ".") {

		getline(cin, user_Input);

		while (user_Input != "") {
			T.oneWordAtATime(user_Input, currentWord);
			if (currentWord == ".")
				break;
			else {
				T.fixWord(currentWord);
				KeyType check = T.approxFind(currentWord);
				if (check == currentWord)
					cout << check << endl;
				else if (check == WORD_FOUND)
					continue;
				else if (check == WORD_NOT_FOUND)
					cout << WORD_NOT_FOUND << endl;
				else
					cout << "Did you mean " << check << "?" << endl;

			}
		}
	}
	return 0;
}

