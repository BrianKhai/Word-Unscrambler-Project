/*
Brian Khai
Homework 3.0
4/18/17
Visual Studio 2015
Hash functions to minimize collisions
*/

#include "Header.h"

// Constructor initializes all the indexs of the table to NULL
HashClass::HashClass() {
	for (int i = 0; i < table_size; i++) {
		HashTable[i] = NULL;
	}
}

// Creates a hash value for a string
// This is what is used for sorting into the table
unsigned HashClass::GenerateHash(string str) {
	unsigned a = 0x811c9dc5;
	unsigned b = 0;
	unsigned hash_value = 0;

	for (int i = 0; i < str.length(); i++) {
		a += str[i];
		b += + a + i;
	}
	hash_value = (a + b);

	return hash_value;

}

// Creates a simple value for a string
// I use this to compare to the scrambled word
// IE: "asdf" and "fdas" have the same simple values
unsigned HashClass::GenerateSimple(string str) {
	int simple_value = 0;
	for (int i = 0; i < str.length(); i++) {
		simple_value += str[i];
	}
	return simple_value;
}

// Takes the hash value, simple value, and word
// and puts it inside the hash table
void HashClass::Hash(string str) {
	unsigned hash_value = GenerateHash(str);
	unsigned simple_value = GenerateSimple(str);
	unsigned i = hash_value % table_size;

	node* nodePtr = HashTable[i];
	node* newPtr = new node;
	newPtr->hash_value = hash_value;
	newPtr->simple_value = simple_value;
	newPtr->entry = str;
	newPtr->next = NULL;
	
	if (!HashTable[i]) {
		HashTable[i] = newPtr;
	} else {
		while (nodePtr->next) {
			nodePtr = nodePtr->next;
		}
		nodePtr->next = newPtr;
	}
}

// ** Looks through each entry then does the following **
// 1. Compares the sum of all the letters added together
// 2. Compares the length of the words
// 3. Compares each letter of words with eachother,
//    if it does it sets that character to NULL and starts
//    over again with the next letter
// 4. If the letter exists it increments a counter
// 5. If the number of letters that exist is the same
//    as the length of the dictionary word then that is 
//    the word
// 6. Print that word and set the function to return true
bool HashClass::SearchHash(string str) {
	bool scrambled_word = false;
	unsigned simple_value = GenerateSimple(str);
	for (int i = 0; i < table_size; i++) {
		node* nodePtr = HashTable[i];
		while (nodePtr) {
			string copy = nodePtr->entry;
			if (nodePtr->simple_value == simple_value && copy.length() == str.length()) {
				int good_letters = 0;
				for (int j = 0; j < str.length(); j++) {
					bool letter_present = false;
					for (int k = 0; k < str.length(); k++) {
						if (str[j] == copy[k]) {
							copy[k] = NULL;
							letter_present = true;
							k = str.length();
						}
					}
					if (letter_present) {
						good_letters++;
					} else {
						j = str.length();
					}
				}
				if (good_letters == copy.length()) {
					cout << nodePtr->entry << endl;
					scrambled_word = true;
				}
			} 
			nodePtr = nodePtr->next;
		}
	}

	return scrambled_word;
}

// Goes through each entry and hash value and prints it
// Tells the collisions of each bucket
void HashClass::Print() {
	for (int i = 0; i < table_size; i++) {
		int collisions = -1;
		cout << i << endl;
		node* nodePtr = HashTable[i];
		while (nodePtr) {
			cout << setw(35) << left << nodePtr->entry ;
			cout << nodePtr->hash_value << endl;
			nodePtr = nodePtr->next;
			collisions++;
		}
		if (collisions < 0) {
			collisions = 0;
		}
		cout << setw(35) << "" << "Collisions: " << collisions << endl;
		cout << endl;
	}
}

// The menu is mostly complete
int main() {
	HashClass a;
	string current_word;
	string word_to_check;
	ifstream dictionary;
	bool good_input = true;
	dictionary.open("projdictionary.txt");

	while (getline(dictionary, current_word)) {
		a.Hash(current_word);
	}
	a.Print();
	dictionary.close();

	do {
		cout << "[U]nscramble a word\n";
		cout << "[P]rint dictionary\n";
		cout << "[Q]uit\n";
		getline(cin, word_to_check);

		if (word_to_check == "u" || word_to_check == "U") {
			cout << "Input a word to search!\n";
			getline(cin, word_to_check);
			cout << "Your word appears to be...\n";
			if (a.SearchHash(word_to_check)) {
			} else {
				cout << "Not in our dictionary!\n";
			}
		} else if (word_to_check == "p" || word_to_check == "P") {
			a.Print();
		} else if (word_to_check == "q" || word_to_check == "Q") {
			good_input = false;
			cout << "Thank you for using our program!\n";
		} else {
			cout << "Invalid input!\n";
		}
		
	} while (good_input);

	system("PAUSE");
	return 0;
}
