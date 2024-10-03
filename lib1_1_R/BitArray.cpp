#include <iostream>
#include <cstring>
#include "Globals.h"

const int universeSize = 10;


void createSet(const char A[], bool bitA[]) 
{
    for (int i = 0; i < universeSize; i++)
        bitA[i] = false;

    for (int i = 0; i < powerOfSet; i++)
    {
        int index = A[i] - '0';
        bitA[index] = true;
    }
}

void setUnion(const bool setA[], const bool setB[], bool result[]) 
{
    for (int i = 0; i < universeSize; i++)
        result[i] = setA[i] || setB[i];

}

void setIntersection(const bool setA[], const bool setB[], bool result[]) 
{
    for (int i = 0; i < universeSize; i++)
        result[i] = setA[i] && setB[i];

}
void processInputBit(const bool bitA[], const bool bitB[], const bool bitC[], const bool bitD[], bool tempABC[])
{
    bool tempBC[universeSize];

    setIntersection(bitB, bitC, tempBC);

    setUnion(bitA, tempBC, tempABC);

    setUnion(tempABC, bitD, tempABC);
}