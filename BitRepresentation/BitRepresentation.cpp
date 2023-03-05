#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "BitRepresentation.h"


template<typename T>
BitRepresentation<T>::BitRepresentation(T number) : data(number) {};

template<typename T>
BitRepresentation<T>::BitRepresentation(vector<bool> &bitRep)
{
	data = 0;
    // Iterate through the elements of the vector in reverse order
    for (int i = bitRep.size() - 1; i >= 0; i--) {
        // Shift the current value of data to the left by 1 bit
        data <<= 1;
        if (bitRep[i]) 
        {
            data |= 1; //Or the data with 1
        }
    }
}

template<typename T>
string BitRepresentation<T>::getBinary()
{
    string binary;
    T copy = data; //Copy to not change the original value
    for (int i = 0; i < sizeof(T) * 8; i++) //Goes through every bit
    {
        bool bit = copy & 1;
        binary += bit ? '1' : '0'; //Adds binary if bit is true otherwise add 0
        copy >>= 1;
    }

    string reversedBinary = toReverse(binary);
    return reversedBinary;
}

template<typename T>
void BitRepresentation<T>::setBit(unsigned int location)
{
    if (location < sizeof(T) * 8) {
        data |= (1 << location); //selects spesific location and turn it into 1
    }
}

template<typename T>
void BitRepresentation<T>::unsetBit(unsigned int location)
{
    if (location < sizeof(T) * 8) 
    {
        data &= ~(1 << location); //selects spesific location and turn it into 0
    }
}

template<typename T>
bool BitRepresentation<T>::isBitSet(unsigned int location)
{
    //
    if(location < sizeof(T) * 8) { //checks if it exceeds the size
        return (data & (1 << location)) != 0; //locates the spesific bit and checks if it is equal to 0
    }
    else
    {
        return false;
    }
}

template<typename T>
string BitRepresentation<T>::getHexadecimal()
{
    string binaryRep = this->getBinary();
  
    string hexRep;
    binaryRep = binaryRep.substr(1, binaryRep.length()); //I don't know there is an error with the first bit

    for (int i = 0; i < binaryRep.size() - 1; i+= 4)
    {
        int hexvalue = 0;
        int power = 8;
        for (int j = 0; j < 4; j++) //To get a value between 15 to 0
        {
            int digit =  binaryRep[i + j]- '0'; //binaryRep[i + j] gets ascii value - '0' can be used to find int value
            hexvalue += digit * power;
            
            power /= 2; // powers go from 8 4 2 1
        }
        
        string hexWanted;

        //Find the corresponding char
        if (hexvalue == 15)
        {
            hexWanted = "F";
        }
        else if (hexvalue == 14)
        {
            hexWanted = "E";
        }
        else if (hexvalue == 13)
        {
            hexWanted = "D";
        }
        else if (hexvalue == 12)
        {
            hexWanted = "C";
        }
        else if (hexvalue == 11)
        {
            hexWanted = "B";
        }
        else if (hexvalue == 10)
        {
            hexWanted = "A";
        }
        else
        {
            hexWanted = to_string(hexvalue);
        }

        hexRep += hexWanted;
    }


    return hexRep;

}


template<typename T>
T BitRepresentation<T>::getNumber()
{
    return data;
}

string toReverse(string regular)
{
    string reversed;
    for (int i = regular.length(); 0 <= i ; i--)
    {
        reversed += regular[i];
    }
    return reversed;
}


