//Dan Lesko

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

template <typename HashedObj>
class QuadHashTable
{
  public:
	  //constructor definition 
	  //will accepts N I M R values and creates an array of size M
    explicit QuadHashTable(int numInts, int interval, int size, int primeLessThanM ) : array( size  )
	{ 
		//inititalization of N I M and R
		  numIntegers = numInts;
		  intervalValue = interval;
		  M = size;
		  R = primeLessThanM;
		  //initialization of variables to assist in table construction
		  attempts = 0;
		  successInsert = 0;
		  failInsert = 0;
		  totalProbes = 0;
		  numProbePerInsert = 0;
		  numClusters = 0;
		  maxClusterSize = 0;
		  maxProbes = 0;
		  //call makeEmpty
		  makeEmpty();
	}

    void makeEmpty( )
    {
        for( int i = 0; i < M; i++ )
            array[ i ].info = EMPTY;
    }

	void put(const HashedObj & value)
	{
		//hash the value (same as the findPos function)
		int K = value % M;
		//iterator
		int I = 0;
		//reset numProbeinsert
		numProbePerInsert = 0;
		//this is the final value after probing
		int hash;
		//loop thru array m/2 times
		for(int count = 0; count < M; count ++)
		{
			//qudratic probe function
			hash = (K + I*I)%M;
			totalProbes++;//increment each time thru
			numProbePerInsert++;//increment each time thru
			if (array[hash].info == EMPTY)//if info is equal to empty
			{
				array[hash].element = value;//assign value to hashed bucket
				array[hash].info = ACTIVE;//set status to active
				successInsert++;//increase
				attempts++;//increase
				if (numProbePerInsert > maxProbes)
					maxProbes = numProbePerInsert;//set maxProbes 
				results();//call results 
				return;//get out of function
			}
			//if we have a match (FAIL CASE)
			if (I > 0 && K == hash)
			{
				failInsert++;//increment
				attempts++;//inrement
				if (numProbePerInsert > maxProbes)
					maxProbes = numProbePerInsert;//set maxProbes to numProbes if its greater
				results();//call results
				return;//break out
			}
				I++;//increment
		}
		//if we make it thru the while loop a fail has happened(BUT THIS WONT HAPPEN!)
		//keep it just in case
		failInsert++;//increment
		attempts++;//increment
		results();//call results
	}

	//function for displaying the actual tables
	void retrieveTable()
	{
		int arraySize = array.size();
		for (int i = 0; i < arraySize; i++)
		{
			int value = array[i].element;
			if (!value)
				cout<<"Position: "<<i + 1<<" Element: Null"<<endl;
			else
				cout<<"Position: "<<i + 1<<" Element: "<<value<<endl;
		}
		cout << endl;
	}

	//results definition
	void results()
	{
		//this call makes it so that we append to the end of the file
		ofstream outFile("results.txt", ios::out | ios::app);
		outputResults(outFile);//call output results
		outFile.close();//close the file
	}

	void outputResults(ofstream & out)
	{
		//this is for the first time through to set up table heading
			if (successInsert <=1 )
			{
				out << "\t\tQuadratic Probing Analysis (Table Size = " << M << " )" << endl;
				out << "\t    --- Inserts ---  ------- Probes -------  ----- Clusters -----" << endl;
				out << setw(5) << "N" << setw(7) << "lambda" <<setw(8) << "success" << setw(7) << "failed";
				out << setw(8) << "total" << setw(6) << "avg" << setw(8) << "max";
				out << setw(10) << "number" << setw(6) << "avg" << setw(8) << "max" << endl;
			}
		//all this code is for one like in the table
			if (attempts % intervalValue == 0)//if attemps mod intervalValue is equal to 0, we send info to file
			{
				//create lambda and avgProbe up
				float lambda = static_cast<float>(successInsert) / static_cast<float>(M);
				float avgProbes = static_cast<float>(totalProbes) / static_cast<float>(attempts);
				out << right <<  setw(5) << attempts;
				out << right << setw(7) << setprecision(2) << fixed << lambda;
				out << setw(7) << successInsert << setw(7) << failInsert;
				out << setw(7) << totalProbes << setw(8) << avgProbes << setw(8) << maxProbes;
				//reset these variables every time for clusters
				int cluster1 = 0;
				int cluster2 = 0;
				numClusters=0;
				int clusterTotal = 0;
				//loop to move through the table to count clusters
				for (int i = 0; i<M; i++)
				{
					if (array[i].info == ACTIVE)//if there is an element in a the bucket
					{
						if ((i-1) >=0)//if we are not out of bounds
						{
							if (array[i-1].info == EMPTY)//and if the previous bucket was empty
								cluster1 = 0; //set cluster1 back to 0
						}
						cluster1++;//increment cluster1
					}
					if (array[i].info == EMPTY)//if the bucket is empty
					{
						if ((i-1) >= 0)//if we are not out of bounds
						{
							if(array[i-1].info != EMPTY)//and if the previous bucket was active
							{
								clusterTotal += cluster1;
								numClusters++;//increment the number of clusters
							}
						}
						if (cluster2 < cluster1)//if cluster2 is less than cluster1
						{
							cluster2 = cluster1;//cluster2 is set equal to cluster1
							maxClusterSize = cluster1;//max clustersize is equal to cluster 1
						}
					}
				}
				//if we make it through the table without finding any empty slots
				if(array[M-1].info == ACTIVE)
				{
					numClusters++;
					clusterTotal+=cluster1;
					if(cluster1 > maxClusterSize)//if cluster1 is bigger, we havent updated max yet
						maxClusterSize = cluster1;//set max to cluster1
				}

				//set up avgClustersize
				float avgClusterSize = static_cast<float>(clusterTotal) / static_cast<float>(numClusters);
				out << setw(8) << numClusters << setw(8) << avgClusterSize << setw(8) << maxClusterSize << endl;
			}
			//this gives us spaces between the tables
			if (attempts == numIntegers)
				out << endl << endl;
	}

	//enum types
    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:

	  //all the variables needed for the hash table and subsequent display table
	int numIntegers;
	int intervalValue;
	int M;
	int R;
	int attempts;
	int successInsert;
	int failInsert;
	int totalProbes;
	int numProbePerInsert;
	int maxClusterSize;
	int numClusters;
	int maxProbes;

	//a struct element that accepts an element and info (will only be used for ints this project)
	//code must be added if we want to hash strings
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
          : element( e ), info( i ) { }
    };
    
	//create array
    vector<HashEntry> array;
    
};

#endif