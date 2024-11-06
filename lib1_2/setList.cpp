#include "setList.h"
#include "Globals.h"
#include <iostream>
#include <ostream>

setList::setList() : head(nullptr) { /*std::cout << "default constructor called" << std::endl;*/ }

setList::setList(const char input[])
{
    head = nullptr;
    for (int i = 0; i < powerOfSet; i++)
    {
        if (i == 0)
            head = init(input[i]);
        else
            addFront(head, input[i]);
    }
    //std::cout << "string constructor called" << std::endl;
}

setList::List* setList::init(char value)
{
    List* node = new List;
    node->value = value;
    node->next = nullptr;

    return node;

    //std::cout << "init called" << std::endl;
}

void setList::addFront(List*& node, char value)
{
    List* temp = init(value);
    if (node == nullptr)
    {
        node = temp;
        return;
    }
    List* tmp = node;
    while (tmp->next != nullptr)
        tmp = tmp->next;

    tmp->next = temp;

    //std::cout << "add front called" << std::endl;
}


std::ostream& operator<<(std::ostream& sys, const setList& SetList)
{
    setList::List* current = SetList.head;
    while (current != nullptr)
    {
        sys << current->value;
        current = current->next;
    }
    return sys;
}

void setList::addBack(List*& node, char value)
{
    List* temp = init(value);
    temp->next = node;

    node = temp;
    //std::cout << "add back called" << std::endl;
}

bool setList::existsInList(List* head, char data)
{
    bool flag = false;
    List* temp = head;
    while (temp != nullptr)
    {
        if (temp->value == data)
            flag = true;

        temp = temp->next;
    }
    //std::cout << "exists in list called" << std::endl;
    return flag;
}

setList setList::processInput(setList A, setList B, setList C, setList D)
{
    setList E = setList();

    List* tempA = A.head;
    while (tempA != nullptr)
    {
        addBack(E.head, tempA->value);
        tempA = tempA->next;
    }

    List* tempB = B.head;
    while (tempB != nullptr)
    {
        if (existsInList(C.head, tempB->value) && !existsInList(E.head, tempB->value))
            addBack(E.head, tempB->value);

        tempB = tempB->next;
    }

    List* tempD = D.head;
    while (tempD != nullptr)
    {
        if (!existsInList(E.head, tempD->value))
            addBack(E.head, tempD->value);

        tempD = tempD->next;
    }
    //std::cout << "process input called" << std::endl;
    return E;
}

//setList::~setList()
//{
//    delete this->head;
//}
