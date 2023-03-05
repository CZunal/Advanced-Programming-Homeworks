#ifndef _BITREPRESENTATION_H
#define _BITREPRESENTATION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


template <typename T>
class BitRepresentation
{
public:
	BitRepresentation(T number); //Constructor tha takes a value as its parameter
	BitRepresentation(std::vector<bool>& bitRep); //Constructor tha takes a boolean list as its parameter
	string getBinary(); //Gets value in binary format 11001000
	string getHexadecimal(); //Gets value in hexadecimal format 11001000
	T getNumber(); //Get the private value data
	void setBit(unsigned int location); //Sets the bit in the given location
	void unsetBit(unsigned int location); //Unsts the bit in the given location
	bool isBitSet(unsigned int location); //Checks if the bit is 1 in the given location

private:
	T data;
};

//Extra functions:
string toReverse(string regular);


//Solution 2 of the Fundamental Dilemma, I also didn't include BitRepresentation.cpp to the project from the settings
#include "BitRepresentation.cpp"
#endif