#define _CRT_SECURE_NO_WARNINGS

#include "SetArray.h"
#include "Globals.h"
#include <iostream>
#include <cstring>

SetArray::SetArray(const char* input) 
{
    n = std::min((int)strlen(input), powerOfSet);
    strncpy(arr, input, n);
    arr[n] = '\0';

    std::cout << "string constructor called" << std::endl;
}

SetArray::SetArray(const SetArray& other) : n(other.n)
{
    this->arr = new char[11];
    strcpy(arr, other.arr);

    std::cout << "Set copy constructor called for Set " << std::endl;
}

SetArray::SetArray() {
    for (int i = 0; i < 10; i++)
		arr[i] = '\0';
    std::cout << "default constructor called" << std::endl;
}

std::ostream& operator<< (std::ostream& sys, const SetArray& setArray)
{
    sys << setArray.arr;
	return sys;
}

SetArray SetArray::operator&(const SetArray& other) const
{
    SetArray result;
    for (int i = 0; i < n; ++i)
        if (strchr(other.arr, arr[i]))
            result.arr[result.n++] = arr[i];

    result.arr[result.n] = '\0';
    std::cout << "operator & called" << std::endl;
    return result;
}

SetArray SetArray::operator|(const SetArray& other) const
{
    SetArray result(*this);
    for (int i = 0; i < other.n; ++i)
        if (!strchr(result.arr, other.arr[i]))
            result.arr[result.n++] = other.arr[i];

    result.arr[result.n] = '\0';
    std::cout << "operator | called" << std::endl;
    return result;
}

SetArray& SetArray::operator=(const SetArray& other)
{
    if (this != &other) 
    {
        delete[] arr;
        arr = new char[11];
        n = other.n;
        strcpy(arr, other.arr);
    }
    std::cout << "operator = called" << std::endl;
    return *this;
}

SetArray::~SetArray()
{
    std::cout << "Set destructor called" << std::endl;
    delete[] arr;
}
