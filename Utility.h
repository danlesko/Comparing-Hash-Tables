//dan lesko

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <fstream>

class Utility{

public:
/**********************************************************************
 * Name: Lower (Static)
 * PreCondition: String.
 * 
 * PostCondition:  Lower case version of string.
 *********************************************************************/
static std::string Lower(std::string inString);


/**********************************************************************
 * Name: Strip (Static)
 * PreCondition: String.
 * 
 * PostCondition:  Returns string of just alpha characters.
 *********************************************************************/
static std::string Strip(std::string inString);


/**********************************************************************
 * Name: FileExisits (Static)
 * PreCondition: Name of file to check for.
 * 
 * PostCondition:  Bool True if the file is available.
 *********************************************************************/
static bool FileExists(const char* filename);
};


#endif