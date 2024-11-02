#include "SetBoolArray.h"
#include "Globals.h"


SetBoolArray::SetBoolArray() { this->arr = new bool[11]; }

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
}

SetBoolArray SetBoolArray::operator||(const SetBoolArray& other)
{
    SetBoolArray res;

    for (int i = 0; i < this->universeSize; i++)
        res.arr[i] = this->arr[i] || other.arr[i];

    return res;
}

SetBoolArray SetBoolArray::operator&&(const SetBoolArray& other)
{
    SetBoolArray res;
    for (int i = 0; i < this->universeSize; i++)
        res.arr[i] = this->arr[i] && other.arr[i];

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
    return *this;
}

SetBoolArray SetBoolArray::processInput(SetBoolArray bitA, SetBoolArray bitB, SetBoolArray bitC, SetBoolArray bitD)
{
    return (bitA || (bitB && bitC)) || bitD;
}

//SetBoolArray::~SetBoolArray()
//{
//    delete[] this->arr;
//}

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
