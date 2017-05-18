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
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/*
The program calls the constructor to set all the initial values in the hash table to NULL.
A file reader passes every entry in projdictionary.txt to the hash table. Then, the program
creates a hash value for every entry. When we're searching for unscrambled word the program
takes several steps and outputs the unscrambled word if it can be found. The user can add or
delete words from the dictionary. The user can print out all the entries if they choose so
or to print every word with extra information.
*/
class HashClass {
	static const unsigned table_size = 29;
	struct node {
		unsigned hash_value;
		string entry;
		shared_ptr<node> next;
	};
	shared_ptr<node> HashTable[table_size];
	
	// Creates a hash value from a string
	unsigned GenerateHash(string str);

public:
	// Initialize each index to NULL
	HashClass();

	// Add word to the hash table
	void AddWord(string str);

	// Delete word from the hash table
	void DeleteWord(string str);

	// Searches dictionary for word
	string SearchHash(string str);

	// Prints every hash value in the table
	void PrintHash();

	// Prints every word in the table
	void Print();
};
