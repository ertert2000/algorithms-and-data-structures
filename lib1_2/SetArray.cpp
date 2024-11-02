#include "SetArray.h"
#include "Globals.h"
#include <iostream>


SetArray::SetArray(char arr[]) {
	int i = 0;
	while (arr[i] != '\0') {
		this->arr[i] = arr[i];
		i++;
	}
    this->arr[i] = '\0';
}

SetArray::SetArray() {
	int j = 0;	for (int i = 0; i < 10; i++)
		arr[i] = '\0';
}

std::ostream& operator<< (std::ostream& sys, const SetArray& setArray)
{
	sys << setArray.arr;
	return sys;
}

int SetArray::len()
{
    int res = 0;
    while (arr[res] != '\0')
        res++;

    return res;
}

SetArray SetArray::processInput(SetArray A, SetArray B, SetArray C, SetArray D)
{
    
    SetArray E;
    int sizeOutputArr = powerOfSet;

    for (int i = 0; i < powerOfSet; i++)
        E.arr[i] = A.arr[i];

    bool flag;
    for (int i = 0; i < powerOfSet; i++)
    {
        flag = true;
        for (int j = 0; j < powerOfSet; j++)
            if (B.arr[i] == E.arr[j])
                flag = false;

        for (int j = 0; j < powerOfSet; j++)
            if (B.arr[i] == C.arr[j] && B.arr[j] != E.arr[i] && flag)
            {
                E.arr[sizeOutputArr] = B.arr[i];
                sizeOutputArr++;
            }

    }

    int s = sizeOutputArr;
    for (int i = 0; i < powerOfSet; i++)
    {
        flag = true;
        for (int j = 0; j < s; j++)
            if (E.arr[j] == D.arr[i])
                flag = false;

        for (int j = i; j < s; j++)
            if (E.arr[j] != D.arr[i] && flag)
            {
                E.arr[sizeOutputArr] = D.arr[i];
                sizeOutputArr++;
                break;
            }

    }

    return E;
}

//SetArray::~SetArray()
//{
//    delete[] this->arr;
//}
