//filename: EmailChecker.cpp
//
//Name: Alan Cabiness
//
//ID: 1461515
//
//Program Description:
//	CSC 309 HW3. See if email adresses are valid

#include <iostream>
#include <fstream>  // for ifstream
#include <cstdlib>  // for exit()
#include <cstring>  // for string-handling functions
using namespace std;

// prototypes
//....
bool oneAt(const char email[]);
bool nonblankAt(const char email[]);
bool oneDot(const char email[]);
bool nonblankDot(const char email[]);

bool oneAt(const char email[]) {
	int count = 0;
	for (int i = 0; i < strlen(email); i++) {
		if (email[i] == '@'){
			count++;
		}
	}
	if (count != 1) {
		return false;
	}
	return true;
}

bool nonblankAt(const char email[]) {
	int at;
	for (int i = 0; i < strlen(email); i++) {
		if (email[i] == '@') {
			at = i;
		}
	}
	if (at == 0 || at==strlen(email)-1) {
		return false;
	}
	if (isalnum(email[at - 1]) && isalnum(email[at + 1])) {
		return true;
	}
	return false;
}

bool oneDot(const char email[]) {
	int dot = 0;
	for (int i = 0; i < strlen(email); i++) {
		if (email[i] == '.') {
			dot++;
		}
	}
	if (dot >= 1) {
		return true;
	}
	return true;
}

bool nonblankDot(const char email[]) {
	int dotcount = 0;
	int dot[10];
	int truecount = 0;
	for (int i = 0; i < strlen(email); i++) {
		if (email[i] == '.') {
			dot[dotcount] = i;
			dotcount++;
		}
	}
	if (dot[0] == 0 || dot[dotcount-1] == strlen(email)-1) {
		return false;
	}
	for (int i = 0; i < dotcount; i++) {
		if (isalnum(email[dot[i] - 1]) && isalnum(email[dot[i] + 1])) {
			truecount++;
			if (truecount == dotcount) {
				return true;
			}
		}
	}
	return false;
}

int main()
{
	char filename[16];
	ifstream fin;

	/* Receive input file name as input. */
	cout << "Enter the input file: ";
	cin >> filename;

	/* Open the input file for reading.  If error, exit the program. */
	fin.open(filename);
	if (fin.fail()) {
		cerr << "Input file opening error.\n";
		exit(1);
	}
	int linenumber = 0;
	/* Declare some variables. */
	const int SIZE = 50;  // should do for this program
	char line[SIZE];

	/* Process one line at a time */
	// Read the first line from the input file
	fin.getline(line, SIZE);
	linenumber++;
	// Process loop
	cout << "***Invalid Entries***" << endl;
	bool valid = true;
	while (strlen(line) != 0)  // as long as the line is not blank
	{
		valid = oneAt(line);
		if (valid == true) {
			valid = nonblankAt(line);
		}
		if (valid == true) {
			valid = oneDot(line);
		}
		if (valid == true) {
			valid = nonblankDot(line);
		}

		if (valid == false) {
			cout << linenumber << ": ";
			for (int z = 0; z < strlen(line); z++) {
				cout << line[z];
			}
			cout << endl;
		}
		// Read the next line from the input file
		fin.getline(line, SIZE);
		linenumber++;
	}

	/* Close the input file before exit. */
	fin.close();

	system("pause");
	return 0;
}