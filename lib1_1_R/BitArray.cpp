#include <iostream>

void setBit(char* bitArray, int index)
{
    bitArray[index / 8] |= (1 << (index % 8));
}

bool isBitSet(const char* bitArray, int index)
{
    return bitArray[index / 8] & (1 << (index % 8));
}

void printBitArray(const char* bitArray)
{
    for (int i = 0; i < 11; i++)
        if (isBitSet(bitArray, i))
            std::cout << i << " ";

    std::cout << std::endl;
}

void createBitArray(const char* arr, int size, char* bitArray)
{
    for (int i = 0; i < size; i++)
        setBit(bitArray, arr[i] - '0');

}

void fifthSetBitwise(const char* A, const char* B, const char* C, const char* D, int size, char* E)
{
    char B_bit[2] = { 0 };
    char C_bit[2] = { 0 };

    createBitArray(A, size, E);

    createBitArray(B, size, B_bit);
    createBitArray(C, size, C_bit);

    for (int i = 0; i < size; i++)
    {
        bool flag = true;
        if (isBitSet(B_bit, A[i] - '0') || isBitSet(C_bit, A[i] - '0'))
            flag = false;

        for (int j = 0; j < size && flag; j++)
            if (isBitSet(B_bit, B[i] - '0') && isBitSet(C_bit, C[j] - '0') && !isBitSet(E, B[i] - '0'))
                setBit(E, B[i] - '0');

    }

    for (int i = 0; i < size; i++)
        if (!isBitSet(E, D[i] - '0'))
            setBit(E, D[i] - '0');

}