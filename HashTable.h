// Pocholo Gayan
// 4-17-13
// This is the declaration and implementation of the HashTable (Hashmap) template class
// This particular HashTable uses chaining and hashes STRING key values

#pragma once
#include <vector>
#include <list>
#include <string>
using std::pair;
using std::vector;
using std::list;
using std::iterator;
using std::string;

#define INITIAL_CAPACITY				100
#define MAX_LOAD_BEFORE_REHASH			2.0
#define HASH_PRIME						1610612741
// 31, 53, 97, 1610612741 - primes

template<typename DATA_TYPE>
class HashTable
{
public:

	// default constructor, empty hash table, sets size
	HashTable(size_t size = INITIAL_CAPACITY): table(size)
	{
		numKeys = 0;
		primeTableSizes[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,47, 
										53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
										113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 
										191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 
										263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 
										347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 
										421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 
										499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 
										593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 
										661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 
										757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 
										853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 
										941, 947, 953, 967, 971, 977, 983, 991, 997};
	}

	// see if parameter can be inserted into list
	void Insert(const pair<const string&, DATA_TYPE>& element)
	{
		// Re-hash, if the number of keys exceeds the table size by at least 2 factors
		if ( ( double (numKeys) / table.size() ) > MAX_LOAD_BEFORE_REHASH )
		{
			int newTableSize;
			for (unsigned int i = 0; primeTableSizes[i] < table.size(); i++)
			{
				newTableSize = primeTableSizes[i];
			}

			vector< list<pair<const string, DATA_TYPE>> > newTable(newTableSize);

			table.swap(newTable);

			for (unsigned int i = 0; i < newTable.size(); i++)
			{
				table[i] = newTable[i];
			}
		}

		// Determine exact position of element in the hash table
		size_t hash = HashCode(element.first);
		size_t index = hash % table.size();

		// first element of list under the ascertained index
		list<pair<const string, DATA_TYPE>>::iterator it = table[index].begin();

		// Search for key , index = key, searches until the end of linked list in bucket 
		while ( it != table[index].end() && it->first != element.first )
		{
			++it;
		}

		// Search found pair not in hash table, insert into bucket
		if ( it == table[index].end() )
		{
			cout << "The hash code of " "\"" << element.first << "\"" << " is: " << hash << endl;
			numKeys++;
			table[index].push_back(element);
		}
		else //already exists in the table, no need to insert
		{
			cout << "Element is already present, no need to insert." << endl;
		}
	}

	void Remove(const string& key)
	{
		if ( numKeys != 0 ) // no need to delete if table is empty
		{
			// Re-hash

			// Determine exact position of element in the hash table
			size_t index = HashCode(key) % table.size();


			list<pair<const string, DATA_TYPE>>::iterator it = table[index].begin();
			// loop through linked list until value is found
			while ( it != table[index].end() && it->first != key )
			{
				++it;
			}

			// if iterator is in a valid position that contains equivalent keys then delete
			if ( it != table[index].end() && it->first == key )
			{
				numKeys--;
				table[index].erase(it);
			}
			else
			{
				cout << "Key is not mapped in table, cannot delete respective key's value." << endl;
			}
		}
		else
		{
			cout << "Cannot delete from an empty table." << endl;
		}
	}

	// returns the data value of the key
	DATA_TYPE& operator [] (const string& key) 
	{
		std::pair<string, DATA_TYPE> temp(key, 0); // default value if it isn't present in hash table
		Insert(temp);

		for ( unsigned int i = 0; i < table.size(); i++ )
		{
			list<pair<const string, DATA_TYPE>>::iterator it = table[i].begin();

			while ( it != table[i].end() )
			{
				if ( it->first == key )
				{
					return it->second;
				}
				++it; 
			}
		}
	}

	void PrintTable() const
	{
		cout << "KEY - VALUE" << endl;

		for ( unsigned int i = 0; i < table.size(); i++ )
		{
			list<pair<const string, DATA_TYPE>>::const_iterator it = table[i].begin();
			while ( it != table[i].end() )
			{
				cout << it->first << " - " << it->second << endl;
				++it; 
			}
		}
	}

	int GetSize() const
	{
		return table.size();
	}

private:

	// Finds the hash code of specified key (strings)
	size_t HashCode(const string& key) const
	{
		size_t hash = 0;

		// constructs hash code
		for ( unsigned i = 0; i < key.length(); i++ )
		{
			hash = hash * HASH_PRIME + key[i];
		}

		return hash;
	}

	vector< list<pair<const string, DATA_TYPE>> > table; // vector containing lists of pairs (buckets) 
	size_t numKeys;
	static const int primeTableSizes[168];
};

