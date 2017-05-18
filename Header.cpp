/*
Aaron Carver
Brian Khai
Joey Hwang
John Kwak

CSCI 133 Project
5/18/17
Visual Studio 2015
Unscrambling program with stored dictionary
*/

#pragma once
#include "Header.h"

// Constructor initializes all the indexs of the table to NULL
HashClass::HashClass() {
	for (int i = 0; i < table_size; i++) {
		HashTable[i] = NULL;
	}
}

// Creates a hash value from a string
unsigned HashClass::GenerateHash(string str) {
	unsigned hash_value = 2166136261;
	int length = str.length();
	
	for (int i = 1; i < length; i++) {
		char current_letter = str[i];
		int j = i;

		while (j > 0 && (str[j - 1] > current_letter)) {
			str[j] = str[j - 1];
			j = j - 1;
		}
		str[j] = current_letter;
	}
	
	for (int i = 0; i < length; i++) {
		hash_value *= 16777619;
		hash_value ^= str[i];
	}
	return hash_value;
}

// Takes the hash value and word
// and adds it to the hash table
void HashClass::AddWord(string str) {
	unsigned hash_value = GenerateHash(str);
	unsigned i = hash_value % table_size;

	shared_ptr<node> nodePtr = HashTable[i];
	shared_ptr<node> newPtr(new node);
	newPtr->hash_value = hash_value;
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

// Delete word from the hash table
void HashClass::DeleteWord(string str) {
	unsigned hash_value = GenerateHash(str);
	unsigned i = hash_value % table_size;
	int iteration = 0;
	shared_ptr<node> nodePtr= HashTable[i];
	shared_ptr<node> prevPtr = NULL;
	
	if (!HashTable[i]) {
		cout << "Your word could not be found!\n";
		cout << "----------------------------------------------\n";
		return;
	}
	if (HashTable[i]->entry == str) {
		nodePtr = HashTable[i]->next;
		HashTable[i] = nodePtr;
		cout << "Your word has been deleted!\n";
		cout << "----------------------------------------------\n";
		return;
	} else {
		while (nodePtr) {
			if (nodePtr->entry == str && !nodePtr->next) {
				prevPtr->next = nodePtr->next;
				nodePtr->next = NULL;
				cout << "Your word has been deleted!\n";
				cout << "----------------------------------------------\n";
				return;
			} else if (nodePtr->entry == str && nodePtr->next) {
				prevPtr->next = nodePtr->next;
				cout << "Your word has been deleted!\n";
				cout << "----------------------------------------------\n";
				return;
			}
			prevPtr = nodePtr;
			nodePtr = nodePtr->next;
		}
	}
	cout << "Your word could not be found!\n";
	cout << "----------------------------------------------\n";
}

// ** Compares each entry with the scrambled word doing the following **
// ---------------------------------------------------------------------
// 1. Compares the sum of all the letters added together
// 2. Compares the length of the words
// 3. Compares each letter of words with eachother
//      a) If the letter exists, it sets that character to NULL
//      b) If the letter exists, it increments a counter
// 4. If the number of letters that exist is the same as the length of 
//    the dictionary word then that is the word
// 5. Print the word
// 6. Set the function to return true
string HashClass::SearchHash(string str) {
	string scrambled_word_found;
	unsigned hash_value = GenerateHash(str);
	unsigned i = hash_value % table_size;
	shared_ptr<node> nodePtr = HashTable[i];

	while (nodePtr) {
		string copy = nodePtr->entry;
		int str_length = str.length();
		int copy_length = copy.length();

		if (nodePtr->hash_value == hash_value && copy_length == str_length) {
			int good_letters = 0;

			for (int j = 0; j < str_length; j++) {
				bool letter_present = false;

				for (int k = 0; k < str_length; k++) {
					if (str[j] == copy[k]) {
						copy[k] = NULL;
						letter_present = true;
						k = str_length;
					}
				}

				if (letter_present) {
					good_letters++;
				} else {
					j = str_length;
				}
			}
			if (good_letters == copy_length) {
				scrambled_word_found = nodePtr->entry;
			}
		}
		nodePtr = nodePtr->next;
	}
	return scrambled_word_found;
}

// Goes through each entry and hash value and prints it
// in addition to information on collisions
void HashClass::PrintHash() {
	int total_collisions = 0;
	int max_collisions = 0;

	for (int i = 0; i < table_size; i++) {
		int collisions = -1;

		cout << "Index: " << (i + 1) << endl;
		shared_ptr<node> nodePtr = HashTable[i];

		while (nodePtr) {
			cout << setw(28) << left << nodePtr->entry;
			cout << nodePtr->hash_value << endl;
			nodePtr = nodePtr->next;
			collisions++;
		}
		if (collisions < 0) {
			collisions = 0;
		}
		if (max_collisions <= collisions) {
			max_collisions = collisions;
		}
		total_collisions += collisions;
		cout << setw(28) << "" << "Collisions: "
			<< collisions << endl << endl;
	}
	cout << "----------------------------------------------\n";
	cout << "Table Size: " << table_size << endl;
	cout << "Max Collisions: " << max_collisions << endl;
	cout << "Total Collisions: " << total_collisions << endl;
	cout << "----------------------------------------------\n";
}

// Print every word in table in three collumns
void HashClass::Print() {
	string first_word, second_word, third_word;
	for (int i = 0; i < table_size; i++) {
		shared_ptr<node> nodePtr = HashTable[i];
		while (nodePtr) {
			if (first_word.empty()) {
				first_word = nodePtr->entry;
			} else if (second_word.empty()) {
				second_word = nodePtr->entry;
			} else if (third_word.empty()) {
				third_word = nodePtr->entry;
			} else {
				cout << setw(28) << left << first_word << setw(28)
					<< second_word << third_word << endl << endl;
				first_word = nodePtr->entry;
				second_word = "";
				third_word = "";
			}
			nodePtr = nodePtr->next;
		}
	}
	cout << setw(28) << left << first_word << setw(28)
		<< second_word << third_word << endl << endl;
}
