#include "List.h"
#include "Globals.h"


//new
Set* init(char value)
{
    Set* node = new Set;
    node->value = value;
    node->next = nullptr;

    return node;
}

void addFront(Set*& node, char value)
{
    Set* temp = init(value);
    if (node == nullptr)
    {
        node = temp;
        return;
    }
    Set* tmp = node;
    while (tmp->next != nullptr)
        tmp = tmp->next;

    tmp->next = temp;

}

bool existsInList(Set* head, char data)
{
    bool flag = false;
    Set* temp = head;
    while (temp != nullptr)
    {
        if (temp->value == data)
            flag = true;

        temp = temp->next;
    }
    return flag;
}

void combineLists(Set*& E, Set* A, Set* B, Set* C, Set* D)
{
    Set* tempA = A;
    while (tempA != nullptr) 
    {
        addFront(E, tempA->value);
        tempA = tempA->next;
    }

    Set* tempB = B;
    while (tempB != nullptr)
    {
        if (existsInList(C, tempB->value) && !existsInList(E, tempB->value))
            addFront(E, tempB->value);

        tempB = tempB->next;
    }

    Set* tempD = D;
    while (tempD != nullptr)
    {
        if (!existsInList(E, tempD->value))
            addFront(E, tempD->value);

        tempD = tempD->next;
    }
}

void printList(Set* head)
{
    Set* temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->value;
        temp = temp->next;
    }
}