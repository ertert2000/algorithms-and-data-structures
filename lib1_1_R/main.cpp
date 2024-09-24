#include "List.h"
#include "Array.h"
#include "BitArray.h"
#include "MachineWord.h"
#include "Generator.h"

// ����������� ��� ������ (1).
// списки(1)
// массив битов(�����), (1)
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
    char EBit[2] = { 0 };
    Cat* structA = NULL;
    Cat* structB = NULL;
    Cat* structC = NULL;
    Cat* structD = NULL;
    Cat* structE = NULL;

    unsigned int wordA = setBit('1') | setBit('2') | setBit('3') | setBit('4');
    unsigned int wordB = setBit('1') | setBit('2') | setBit('3') | setBit('4');
    unsigned int wordC = setBit('1') | setBit('2') | setBit('3') | setBit('4');
    unsigned int wordD = setBit('1') | setBit('2') | setBit('3') | setBit('4');

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

    for (auto i : E)
        std::cout << i;

    std::cout << std::endl;

    combineLists(structE, structA, structB, structC, structD);

    printList(structE);
    std::cout << std::endl;

    fifthSetBitwise(A, B, C, D, 4, EBit);

    printBitArray(EBit);
    std::cout << std::endl;

    unsigned int wordE = createFifthSet(wordA, wordB, wordC, wordD);

    displaySet(wordE);
    std::cout << std::endl;

    generateNumbers();
    return 0;
}