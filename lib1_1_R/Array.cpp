
#include "Array.h"

void processInput(const char A[4], const char B[4], const char C[4], const char D[4], char E[11], int& sizeOutputArr) {
    memset(E, '\0', 11);

    sizeOutputArr = 4;

    for (int i = 0; i < 4; i++)
        E[i] = A[i];
    bool flag = true;
    for (int i = 0; i < 4; i++) {
        flag = true;
        for (int j = 0; j < 4; j++) {
            if (B[j] == E[i] || C[j] == E[i])
                flag = false;
        }
        for (int j = 0; j < 4; j++) {
            if (B[i] == C[j] && B[j] != E[i] && flag) {
                E[sizeOutputArr] = B[i];
                sizeOutputArr++;
            }
        }
    }

    flag = true;
    int s = sizeOutputArr;
    for (int i = 0; i < 4; i++)
    {
        flag = true;
        for (int j = 0; j < s; j++) {
            if (E[j] == D[i])
                flag = false;
        }
        for (int j = i; j < s; j++)
        {
            if (E[j] != D[i] && flag)
            {
                E[sizeOutputArr] = D[i];
                sizeOutputArr++;
                break;
            }
        }
    }
}