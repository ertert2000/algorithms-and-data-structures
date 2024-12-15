#include "SetBoolArray.h"
#include "Globals.h"


SetBoolArray::SetBoolArray() { this->arr = new bool[11]; std::cout << "default constructor called" << std::endl; }

SetBoolArray::SetBoolArray(const char input[])
{
    this->arr = new bool[11];

    for (int i = 0; i < universeSize; i++)
        this->arr[i] = false;

    for (int i = 0; i < powerOfSet; i++)
    {
        int index = input[i] - '0';
        this->arr[index] = true;
    }
    std::cout << "string constructor called" << std::endl;
}

SetBoolArray::SetBoolArray(const SetBoolArray& other) : arr(other.arr) { std::cout << "Set copy constructor called for Set " << std::endl; }

SetBoolArray SetBoolArray::operator|(const SetBoolArray& other)
{
    SetBoolArray res;

    for (int i = 0; i < this->universeSize; i++)
        res.arr[i] = this->arr[i] || other.arr[i];

    std::cout << "operator | called" << std::endl;
    return res;
}

SetBoolArray SetBoolArray::operator&(const SetBoolArray& other)
{
    SetBoolArray res;
    for (int i = 0; i < this->universeSize; i++)
        res.arr[i] = this->arr[i] && other.arr[i];

    std::cout << "operator & called" << std::endl;
    return res;
}

SetBoolArray& SetBoolArray::operator=(const SetBoolArray& other) 
{
    if (this != &other) 
    {
        delete[] arr;
        arr = new bool[universeSize]();
        std::memcpy(arr, other.arr, universeSize * sizeof(bool));
    }
    std::cout << "operator = called" << std::endl;
    return *this;
}

SetBoolArray::~SetBoolArray()
{
    std::cout << "Bool destructor called" << std::endl;
    delete[] arr;
}

std::ostream& operator<<(std::ostream& sys, const SetBoolArray& SetList)
{
    char res[11];
    int sizeOutputArr = 0;
    int i = 0;

    for (int i = 0; i < 10; i++)
        if (SetList.arr[i])
            res[sizeOutputArr++] = '0' + i;

    res[sizeOutputArr] = '\0';

    while (res[i] != '\0')
    {
        sys << res[i];
        i++;
    }

    return sys;
}
