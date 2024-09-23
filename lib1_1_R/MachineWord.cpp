#include <iostream>


unsigned int setBit(char c) 
{
    return 1 << (c - '0');
}


unsigned int createFifthSet(unsigned int A, unsigned int B, unsigned int C, unsigned int D) 
{
    unsigned int E = A;

    for (char i = '0'; i <= '9'; i++) 
    {
        unsigned int mask = setBit(i);
        if ((B & mask) && !(C & mask) && !(E & mask))
            E |= mask;
    }

    for (char i = '0'; i <= '9'; i++) 
    {
        unsigned int mask = setBit(i);
        if ((D & mask) && !(E & mask))
            E |= mask;
    }

    return E;
}

void displaySet(unsigned int set) 
{
    for (char i = '0'; i <= '9'; i++)
        if (set & setBit(i))
            std::cout << i << " ";

    std::cout << std::endl;
}

