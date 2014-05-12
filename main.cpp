// Pocholo Gayan
// 4-17-13
// This is the main entry point for the hash table program

#include <iostream>
#include "HashTable.h"
using std::cout;
using std::cin;
using std::endl;
#define END_OF_LOOP 5

void main()
{
	HashTable<char> table(2);
	string key;
	char value;

	// Fill tables
	for (unsigned int i = 0; i < END_OF_LOOP; i++)
	{
		cout << "Enter key: ";
		cin >> key;

		cout << "Enter char: ";
		cin >> value;

		table.Insert( std::pair<string, char>(key, value) );
		cout << endl;
	}

	cout << endl;

	// Remove element from table
	cout << "Select element to remove by inputting key:";
	cin >> key;

	table.Remove(key);

	// Index Operator
	cout << endl << "table[ blue ] = 'F'" << endl;
	table[ "blue" ] = 'F';

	cout << endl;
	
	// Print hash table contents
	table.PrintTable();

	system("pause");
}