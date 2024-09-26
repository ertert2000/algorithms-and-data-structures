#pragma once

#include <iostream>

typedef struct Set
{
    char value;
    struct Set* next;
}Set;

Set* init(char value);

void addFront(Set*& Cola, char value);

void combineLists(Set*& E, Set* A, Set* B, Set* C, Set* D);

void printList(Set* head);