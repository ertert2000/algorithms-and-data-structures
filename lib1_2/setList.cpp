#include "setList.h"
#include "Globals.h"
#include <iostream>
#include <ostream>

setList::setList() : head(nullptr) { std::cout << "default constructor called" << std::endl; }

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
    std::cout << "string constructor called" << std::endl;
}

setList::setList(const setList& other) : head(nullptr)
{
    List* current = other.head;
    while (current) 
    {
        addBack(current->value);
        current = current->next;
    }
    std::cout << "Set copy constructor called for List " << std::endl;
}

setList& setList::operator=(const setList& other)
{
    if (this != &other) 
    {
        clear();
        List* current = other.head;
        while (current) 
        {
            addBack(current->value);
            current = current->next;
        }
    }
    std::cout << "operator = called" << std::endl;
    return *this;
}

setList setList::operator&(const setList& other) const
{
    setList result;
    List* current = head;
    while (current) 
    {
        if (other.exists(current->value))
            result.addBack(current->value);
        current = current->next;
    }
    std::cout << "operator & called" << std::endl;
    return result;
}

setList setList::operator|(const setList& other)
{
    setList result(*this); 
    List* current = other.head;
    while (current) 
    {
        if (!result.exists(current->value))
            result.addBack(current->value);
        current = current->next;
    }
    std::cout << "operator | called" << std::endl;
    return result;
}

setList::List* setList::init(char value)
{
    List* node = new List;
    node->value = value;
    node->next = nullptr;

    return node;

    std::cout << "init called" << std::endl;
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

    std::cout << "add front called" << std::endl;
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

void setList::addBack(char value)
{
    if (!head)
        head = init(value);
    else 
    {
        List* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = init(value);
    }
    std::cout << "add back called" << std::endl;
}


void setList::clear()
{
    while (head) 
    {
        List* temp = head;
        head = head->next;
        delete temp;
    }
}

bool setList::exists(char value) const
{
    std::cout << "exists called" << std::endl;
    List* current = head;
    while (current) 
    {
        if (current->value == value)
            return true;
        current = current->next;
    }
    return false;
}

setList::~setList()
{
    std::cout << "List destructor called" << std::endl;
    clear();
}
