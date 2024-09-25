#include "List.h"
#include "Globals.h"

Cat* init(char value)
{
    Cat* node = (Cat*)malloc(sizeof(Cat));
    if (!(node))
        exit(1);
    node->value = value;

    node->next = NULL;
}

void addFront(Cat*& Cola, char value)
{
    Cat* temp = init(value);
    if (Cola == NULL) 
    {
        Cola = temp;
        return;
    }
    Cat* tmp = Cola;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = temp;

}

bool existsInList(Cat* head, char data)
{
    Cat* temp = head;
    while (temp != nullptr)
    {
        if (temp->value == data)
            return true;

        temp = temp->next;
    }
    return false;
}

void combineLists(Cat*& E, Cat* A, Cat* B, Cat* C, Cat* D)
{
    Cat* tempA = A;
    while (tempA != nullptr) 
    {
        addFront(E, tempA->value);
        tempA = tempA->next;
    }

    Cat* tempB = B;
    while (tempB != nullptr)
    {
        if (existsInList(C, tempB->value) && !existsInList(E, tempB->value))
            addFront(E, tempB->value);

        tempB = tempB->next;
    }

    Cat* tempD = D;
    while (tempD != nullptr)
    {
        if (!existsInList(E, tempD->value))
            addFront(E, tempD->value);

        tempD = tempD->next;
    }
}

void printList(Cat* head)
{
    Cat* temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->value;
        temp = temp->next;
    }
}