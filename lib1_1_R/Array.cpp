#include "Array.h"
#include "Globals.h"

void processInput(const char A[], const char B[], const char C[], const char D[], char E[11], int& sizeOutputArr) {
    memset(E, '\0', 11);

    sizeOutputArr = powerOfSet;

    for (int i = 0; i < powerOfSet; i++)
        E[i] = A[i];

    bool flag;
    for (int i = 0; i < powerOfSet; i++) 
    {
        flag = true;
        for (int j = 0; j < powerOfSet; j++)
            if (B[i] == E[j] || C[i] == E[j])
                flag = false;

        for (int j = 0; j < powerOfSet; j++)
            if (B[i] == C[j] && B[j] != E[i] && flag) 
            {
                E[sizeOutputArr] = B[i];
                sizeOutputArr++;
            }

    }

    int s = sizeOutputArr;
    for (int i = 0; i < powerOfSet; i++)
    {
        flag = true;
        for (int j = 0; j < s; j++)
            if (E[j] == D[i])
                flag = false;

        for (int j = 0; j < s; j++)
            if (E[j] != D[i] && flag)
            {
                E[sizeOutputArr] = D[i];
                sizeOutputArr++;
                break;
            }

    }
}