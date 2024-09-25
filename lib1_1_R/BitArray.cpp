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

void processInputBit(const char A[], const char B[], const char C[], const char D[], char E[], int& sizeOutputArr) 
{
    bool bitA[universeSize], bitB[universeSize], bitC[universeSize], bitD[universeSize];
    bool tempBC[universeSize], tempABC[universeSize];

    createSet(A, bitA);
    createSet(B, bitB);
    createSet(C, bitC);
    createSet(D, bitD);

    setIntersection(bitB, bitC, tempBC);

    setUnion(bitA, tempBC, tempABC);

    setUnion(tempABC, bitD, tempABC);

    sizeOutputArr = 0;
    for (int i = 0; i < universeSize; i++)
        if (tempABC[i])
            E[sizeOutputArr++] = '0' + i;

    E[sizeOutputArr] = '\0';
}