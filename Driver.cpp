//Dan Lesko
//November 18, 2014
//CMSC 341 - COMPARING HASH TABLES PROJECT 4

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleHash.h"
#include "MyExceptions.h"
#include "Utility.h"
using namespace std;


int main(int argc, char *argv[])
{
	//assigns command line arguments to variables
	string filename = argv[1];
	int numInts = atoi(argv[2]);
	int interval = atoi(argv[3]);
	int hashSize = atoi(argv[4]);
	int primeLessThanM = atoi(argv[5]);
	
	//checks for file existence
    if (!(Utility::FileExists(filename.c_str())))
	{
		throw Exceptions(filename + " was not found!");
	}

	//create instream operator
	ifstream inFile(filename.c_str());

	//create instances of each type of hash table
	QuadHashTable<int> quadHash(numInts, interval, hashSize, primeLessThanM);
	LinearHashTable<int> linearHash(numInts, interval, hashSize, primeLessThanM);
	DoubleHashTable<int> doubleHash(numInts, interval, hashSize, primeLessThanM);

	//in order for this program to work we have to loop through the file 3 seperate times

	//first time through
	int inNum;//create variable to take in numbers
	while(inFile >> inNum)
	{
		try
		{
			linearHash.put(inNum);//push numbers to the linear hash table
		}

		catch(Exceptions &cException) 
		{
			cout << "EXCEPTION: " << cException.GetMessage() << endl;
			return 1;
		}

	};
	
	//close file and reopen for second table
	inFile.close();
	ifstream inFile2(filename.c_str());

	//second time thru
	int inNum2;
	while(inFile2 >> inNum2)
	{
		try
		{
			quadHash.put(inNum2);//push numbers the quad hash table
		}

		catch(Exceptions &cException) 
		{
			cout << "EXCEPTION: " << cException.GetMessage() << endl;
			return 1;
		}

	};

	//close and reopen for a third time
	inFile2.close();
	ifstream inFile3(filename.c_str());

	//third time thru
	int inNum3;
	while(inFile3 >> inNum3)
	{
		try
		{
			doubleHash.put(inNum3);//push numbers to doubly hashed table
		}

		catch(Exceptions &cException) 
		{
			cout << "EXCEPTION: " << cException.GetMessage() << endl;
			return 1;
		}

	};

	inFile3.close();

	//output statement once operations have finished
	cout << "Hashing Operations Completed!" << endl;

//	system("pause"); 
    return 0;
}
