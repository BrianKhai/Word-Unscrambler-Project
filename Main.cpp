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

#include "Header.h"

// The menu opens a file and reads it's contents to the hash table creating
// it's associated hashes and storing the data. It prints out the dictionary
// and then main menu which allows the user to select whether he wants to:
// [U]nscramble a word, [A]dd a word, [D]elete a word, [P]rint the dictionary,
// [S]how hash values, or [Q]uit.
int main() {
	HashClass a;
	string current_word;
	string user_input;
	bool user_wishes_to_continue = true;

	ifstream dictionary;
	dictionary.open("projdictionaryHARD.txt");

	while (getline(dictionary, current_word)) {
		a.AddWord(current_word);
	}
	dictionary.close();
	a.Print();

	do {
		cout << "-------------------MAINMENU-------------------\n";
		cout << "[U]nscramble a word\n";
		cout << "[A]dd a word\n";
		cout << "[D]elete a word\n";
		cout << "[P]rint dictionary\n";
		cout << "[S]how hash values\n";
		cout << "[Q]uit\n";
		cout << "----------------------------------------------\n";
		getline(cin, user_input);
		system("CLS");
		if (user_input == "u" || user_input == "U") {
			cout << "----------------------------------------------\n";
			cout << "Input a word to search!\n";
			cout << "----------------------------------------------\n";
			getline(cin, user_input);
			string search_word = a.SearchHash(user_input);
			cout << "Your word appears to be...\n";
			if (!search_word.empty()) {
				cout << search_word << endl;
			}
			else {
				cout << "Not in our dictionary!\n";
			}
			cout << "----------------------------------------------\n";
		}
		else if (user_input == "a" || user_input == "A") {
			cout << "----------------------------------------------\n";
			cout << "Input a word to add!\n";
			cout << "----------------------------------------------\n";
			getline(cin, user_input);
			a.AddWord(user_input);
			cout << "Your word has been added to the dictionary!\n";
			cout << "----------------------------------------------\n";
		} 
		else if (user_input == "d" || user_input == "D") {
			cout << "----------------------------------------------\n";
			cout << "Input a word to delete!\n";
			cout << "----------------------------------------------\n";
			getline(cin, user_input);
			a.DeleteWord(user_input);
		}
		else if (user_input == "p" || user_input == "P") {
			a.Print();
		} else if (user_input == "s" || user_input == "S") {
			a.PrintHash();
		}
		else if (user_input == "q" || user_input == "Q") {
			cout << "----------------------------------------------\n";
			cout << "Are you sure you want to [Q]uit?\n";
			cout << "Press any other key to continue program...\n";
			cout << "----------------------------------------------\n";
			getline(cin, user_input);
			if (user_input == "q" || user_input == "Q") {
				cout << "Thank you for using our program!\n";
				cout << "----------------------------------------------\n";
				user_wishes_to_continue = false;
			}
		} else {
			cout << "----------------------------------------------\n";
			cout << "Invalid input!\n";
			cout << "----------------------------------------------\n";
		}
		system("PAUSE");
		system("CLS");
	} while (user_wishes_to_continue);

	return 0;
}
