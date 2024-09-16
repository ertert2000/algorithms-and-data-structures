#include <iostream>
#include <cstring>

typedef struct Cat
{
    char value;
    struct Cat* next;
}Cat;

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

    //for (int i = 0, j = sizeOutputArr; i != j; i++, j--)
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

int main()
{
    int sizeOutputArr = 4;

    char A[4];
    char B[4];
    char C[4];
    char D[4];
    char E[11];


    std::cout << "Please, enter A\n";
    for (int i = 0; i < 4; i++)
        std::cin >> A[i];

    std::cout << "\nPlease, enter B\n";
    for (int i = 0; i < 4; i++)
        std::cin >> B[i];

    std::cout << "\nPlease, enter C\n";
    for (int i = 0; i < 4; i++)
        std::cin >> C[i];

    std::cout << "\nPlease, enter D\n";
    for (int i = 0; i < 4; i++)
        std::cin >> D[i];


    processInput(A, B, C, D, E, sizeOutputArr);
    //!!!!!!!!!!!!!!!!!!!!!! but 


    //for (int i = 0; i < 4; i++)
    //    E[i] = A[i];
    //bool flag = true;
    //for (int i = 0; i < 4; i++) {
    //    flag = true;
    //    for (int j = 0; j < 4; j++) {
    //        if (B[j] == E[i] or C[j] == E[i])
    //            flag = false;
    //    }
    //    for (int j = 0; j < 4; j++) {
    //        if (B[i] == C[j] and B[j] != E[i] and flag) {
    //            E[sizeOutputArr] = B[i];
    //            sizeOutputArr++;
    //        }
    //    }
    //}

    ////for (int i = 0, j = sizeOutputArr; i != j; i++, j--)
    //flag = true;
    //int s = sizeOutputArr;
    //for (int i = 0; i < 4; i++)
    //{
    //    flag = true;
    //    for (int j = 0; j < s; j++) {
    //        if (E[j] == D[i])
    //            flag = false;
    //    }
    //    for (int j = i; j < s; j++)
    //    {
    //        if (E[j] != D[i]  and flag)
    //        {
    //            E[sizeOutputArr] = D[i];
    //            sizeOutputArr++;
    //            break;
    //        }
    //    }
    //}

    for (auto i : E)
    {
        std::cout << i << std::endl;
    }

    return 0;
}