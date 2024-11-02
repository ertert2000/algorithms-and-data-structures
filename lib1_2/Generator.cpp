#include "Generator.h"
#include "Globals.h"
#include <iostream>
#include <random>
#include <set>

char* generateNumbers()
{
    char* result = new char[11] {0};
    std::set<int> uniqueNumbers;
    std::random_device rnd;
    std::mt19937 gen(rnd());
    std::uniform_int_distribution<> dist(0, 9);

    while (uniqueNumbers.size() < powerOfSet)
    {
        int num = dist(gen);
        uniqueNumbers.insert(num);
    }

    int index = 0;
    for (int num : uniqueNumbers)
        result[index++] = '0' + num;

    return result;
}