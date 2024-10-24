#include "SetBoolArray.h"


SetBoolArray::SetBoolArray() { this->arr = new bool[11]; }

SetBoolArray::SetBoolArray(const char input[])
{
    this->arr = new bool[11];

    for (int i = 0; i < universeSize; i++)
        this->arr[i] = false;

    for (int i = 0; i < 4; i++)
    {
        int index = input[i] - '0';
        this->arr[index] = true;
    }
}

SetBoolArray SetBoolArray::operator||(const SetBoolArray& other)
{
    SetBoolArray res = SetBoolArray();

    for (int i = 0; i < this->universeSize; i++)
        res.arr[i] = this->arr[i] || other.arr[i];

    return res;
}

SetBoolArray SetBoolArray::operator&&(const SetBoolArray& other)
{
    SetBoolArray res = SetBoolArray();
    for (int i = 0; i < this->universeSize; i++)
        res.arr[i] = this->arr[i] && other.arr[i];

    return res;
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
