/*
Brian Khai
Homework 3.0
4/18/17
Visual Studio 2015
Hash functions to minimize collisions
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/*
The program calls the constructor to set all the initial values in the hash table to NULL.
A file reader passes every entry in projdictionary.txt to the hash table. Then, the program
creates a hash value (For sorting) and simple value (To compare when we're unscrambling words)
for every entry. When we're searching for unscrambled word the program takes several steps,
checking every entry, and outputs all the possible unscrambled words. The user can print out
all the entries if they choose so.
*/
class HashClass {
	static const unsigned table_size = 29;
	struct node {
		unsigned hash_value;
		unsigned simple_value;
		string entry;
		node* next;
	};
	node* HashTable[table_size];
	
public:
	// Initialize each index to NULL
	HashClass();
	// Creates a hash value from a string
	unsigned GenerateHash(string str);
	// Creates a simple value from a string
	unsigned GenerateSimple(string str);
	// Puts information in the hash table
	void Hash(string str);
	// Unscrambles word
	bool SearchHash(string str);
	// Prints every value in the table
	void Print();
};