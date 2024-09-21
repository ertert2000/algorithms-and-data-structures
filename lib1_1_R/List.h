#pragma once

#include <iostream>

typedef struct Cat
{
    char value;
    struct Cat* next;
}Cat;

Cat* init(char value);

void addFront(Cat*& Cola, char value);

void combineLists(Cat*& E, Cat* A, Cat* B, Cat* C, Cat* D);

void printList(Cat* head);