#include "Utility.h"
#include <utility>
#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;


//Retuns the string lower cased.
string Utility::Lower(string inString)
{
    //converts all alphas to lowercase
	transform(inString.begin(), inString.end(), inString.begin(), ::tolower); 
    return inString;
}


//Returns the string with only alpha characters.
string Utility::Strip(string inString)
{
    //creates array of punction to check for
	char chars[] = "`().,\"!?:*;/";
	//removes punctuation defined in char array
	for (unsigned int i = 0; i<strlen(chars); ++i)
	{
		inString.erase(remove(inString.begin(), inString.end(), chars[i]), inString.end());
	}
	//erases all digits
	inString.erase(std::remove_if(inString.begin(), inString.end(), ::isdigit), inString.end());
	//removes any punctuation found at beginning of the words
	while (ispunct(inString[0]))
		inString.erase(0,1);

	while(ispunct(inString[inString.length()]))
		inString.erase(inString.length(),1);


	//removes hyphens and apostrophes at the end of the words
	for (int n=inString.length(); n && inString[--n]=='-'; inString.resize(n));
	for (int n=inString.length(); n && inString[--n]=='\''; inString.resize(n));
 
	return inString;
    
}

//returns true of file successfully opens
bool Utility::FileExists(const char* filename)
{
    ifstream inFile(filename);
    
    if (!inFile) {
        return false;
    }
    else {
        inFile.close();
        return true;
    }
}