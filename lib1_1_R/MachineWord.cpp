#include <iostream>
#include <bitset>
#include "MachineWord.h"


//unsigned int setBit(char c) 
//{
//    return 1 << (c - '0');
//}
//
//
//unsigned int createFifthSet(unsigned int A, unsigned int B, unsigned int C, unsigned int D) 
//{
//    unsigned int E = A;
//
//    for (char i = '0'; i <= '9'; i++) 
//    {
//        unsigned int mask = setBit(i);
//        if ((B & mask) && !(C & mask) && !(E & mask))
//            E |= mask;
//    }
//
//    for (char i = '0'; i <= '9'; i++) 
//    {
//        unsigned int mask = setBit(i);
//        if ((D & mask) && !(E & mask))
//            E |= mask;
//    }
//
//    return E;
//}
//
//void displaySet(unsigned int set) 
//{
//    for (char i = '0'; i <= '9'; i++)
//        if (set & setBit(i))
//            std::cout << i << " ";
//
//    std::cout << std::endl;
//}

void createMachineWord(char array[], int len, unsigned int& result) 
{
    result = 0;
    for (int i = 0; i < len; ++i)
        result |= 1 << (array[i] - '0');
}

void printMachineWord(unsigned int word) 
{
    for (int i = 0; i < 9; i++)
        if (word & (1 << i))
            std::cout << static_cast<char>(i + '0');

    std::cout << std::endl;
}