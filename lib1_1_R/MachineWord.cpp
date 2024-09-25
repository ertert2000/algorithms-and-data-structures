#include <iostream>
#include <bitset>
#include "MachineWord.h"
#include "Globals.h"

void createMachineWord(char array[], int len, unsigned int& result) 
{
    result = 0;
    for (int i = 0; i < len; ++i)
        result |= 1 << (array[i] - '0');
}

void printMachineWord(unsigned int word) 
{
    for (int i = 0; i < 10; i++)
        if (word & (1 << i))
            std::cout << static_cast<char>(i + '0');

    std::cout << std::endl;
}