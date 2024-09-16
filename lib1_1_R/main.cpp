#include <iostream>
#include <cstring>

typedef struct Cat
{
    char value;
    struct Cat* next;
}Cat;

void processInput(Cat* structA, Cat* structB, Cat* structC, Cat* structD, Cat* structE, int& sizeOutputArr) {
    
    for (int i = 0; i < 4; i++)
    {
        structE->value = structA->value;

        structE = structE->next;
        structA = structA->next;
    }
    
    
    
    //memset(E, '\0', 11);

    //sizeOutputArr = 4;

    //for (int i = 0; i < 4; i++)
    //    E[i] = A[i];
    //bool flag = true;
    //for (int i = 0; i < 4; i++) {
    //    flag = true;
    //    for (int j = 0; j < 4; j++) {
    //        if (B[j] == E[i] || C[j] == E[i])
    //            flag = false;
    //    }
    //    for (int j = 0; j < 4; j++) {
    //        if (B[i] == C[j] && B[j] != E[i] && flag) {
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
    //        if (E[j] != D[i] && flag)
    //        {
    //            E[sizeOutputArr] = D[i];
    //            sizeOutputArr++;
    //            break;
    //        }
    //    }
    //}
}

Cat* init(char value) {
    Cat* node = (Cat*)malloc(sizeof(Cat));
    if (!(node))
        exit(1);
    node->value = value;

    node->next = NULL;
}

void addFront(char value, Cat** Cola) {
    Cat* temp = init(value);
    Cat* tmp = *Cola;

    while (tmp->next != NULL) 
        tmp = tmp->next;

    tmp->next = temp;
    
}

int main()
{
    int sizeOutputArr = 4;

    char A[4];
    char B[4];
    char C[4];
    char D[4];
    char E[11];
    Cat* structA = NULL;
    Cat* structB = NULL;
    Cat* structC = NULL;
    Cat* structD = NULL;
    Cat* structE = NULL;

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

    for (int i = 0; i < 4; i++) {
        if (i == 0)
            structA = init(A[i]);
        else
            addFront(A[i], &structA);
    }

    for (int i = 0; i < 4; i++) {
        if (i == 0)
            structB = init(B[i]);
        else
            addFront(B[i], &structB);
    }

    for (int i = 0; i < 4; i++) {
        if (i == 0)
            structC = init(C[i]);
        else
            addFront(C[i], &structC);
    }

    for (int i = 0; i < 4; i++) {
        if (i == 0)
            structD = init(D[i]);
        else
            addFront(D[i], &structD);
    }

    for (int i = 0; i < 11; i++) {
        if (i == 0)
            structE = init('\0');
        else
            addFront('\0', &structE);
    }

    processInput(structA, structB, structC, structD, structE, sizeOutputArr);
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