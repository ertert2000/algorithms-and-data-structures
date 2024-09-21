#include "List.h"
#include "Array.h"


// ����������� ��� ������ (1). 
// списки(1)
// массив битов(�����),
// машинное слово,(�������)
// �������� ���������(�����),
// ��������� �������.(�������)

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
            addFront(structA, A[i]);
    }

    for (int i = 0; i < 4; i++) {
        if (i == 0)
            structB = init(B[i]);
        else
            addFront(structB, B[i]);
    }

    for (int i = 0; i < 4; i++) {
        if (i == 0)
            structC = init(C[i]);
        else
            addFront(structC, C[i]);
    }

    for (int i = 0; i < 4; i++) {
        if (i == 0)
            structD = init(D[i]);
        else
            addFront(structD, D[i]);
    }

    structE = init(NULL);

    processInput(A, B, C, D, E, sizeOutputArr);

    combineLists(structE, structA, structB, structC, structD);

    printList(structE);

    return 0;
}