#include "List.h"
#include "Array.h"
#include "BitArray.h"
#include "MachineWord.h"
#include "Generator.h"
#include "Globals.h"
#include <ctime>
#include <chrono>



#define MAXSIZE 11
// ����������� ��� ������ (1).
// списки(1)
// массив битов(�����), (1)
// машинное слово,(�������)
// �������� ���������(�����),
// ��������� �������.(�������)

int main()
{
    srand(time(nullptr));

    std::cout << "Input power of set: ";
    std::cin >> powerOfSet;
    std::cout << std::endl;

    int sizeOutputArr = powerOfSet;
    int sizeOutputArrBit = powerOfSet;

    char* A = generateNumbers();
    char* B = generateNumbers();
    char* C = generateNumbers();
    char* D = generateNumbers();
    char E[MAXSIZE];
    char EBit[MAXSIZE];
    Cat* structA = NULL;
    Cat* structB = NULL;
    Cat* structC = NULL;
    Cat* structD = NULL;
    Cat* structE = NULL;

    for(int i = 0; i < powerOfSet; i++)
        std::cout << A[i];
    std::cout << std::endl;
    for (int i = 0; i < powerOfSet; i++)
        std::cout << B[i];
    std::cout << std::endl;
    for (int i = 0; i < powerOfSet; i++)
        std::cout << C[i];
    std::cout << std::endl;
    for (int i = 0; i < powerOfSet; i++)
        std::cout << D[i];
    std::cout << std::endl;




    //Array
    auto startArray = std::chrono::high_resolution_clock::now();
    processInput(A, B, C, D, E, sizeOutputArr);

    auto endArray = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationArray = endArray - startArray;
    std::cout << "Execution time for array: " << durationArray.count() << " seconds\n";

    for (auto i : E)
        std::cout << i;

    std::cout << std::endl;




    //List
    auto startList = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < powerOfSet; i++) {
        if (i == 0)
            structA = init(A[i]);
        else
            addFront(structA, A[i]);
    }

    for (int i = 0; i < powerOfSet; i++) {
        if (i == 0)
            structB = init(B[i]);
        else
            addFront(structB, B[i]);
    }

    for (int i = 0; i < powerOfSet; i++) {
        if (i == 0)
            structC = init(C[i]);
        else
            addFront(structC, C[i]);
    }

    for (int i = 0; i < powerOfSet; i++) {
        if (i == 0)
            structD = init(D[i]);
        else
            addFront(structD, D[i]);
    }

    combineLists(structE, structA, structB, structC, structD);

    auto endList = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationList = endList - startList;
    std::cout << "Execution time for lists: " << durationList.count() << " seconds\n";

    printList(structE);
    std::cout << std::endl;



    //Bit Array
    auto startBitArray = std::chrono::high_resolution_clock::now();
    processInputBit(A, B, C, D, EBit, sizeOutputArrBit);

    auto endBitArray = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationBitArray = endBitArray - startBitArray;
    std::cout << "Execution time for bit array: " << durationBitArray.count() << " seconds\n";

    for (int i = 0; i < sizeOutputArrBit; i++)
        std::cout << EBit[i];

    std::cout << "\n";




    //MachineWord
    unsigned int wordA;
    unsigned int wordB;
    unsigned int wordC;
    unsigned int wordD;
    unsigned int wordUnionAD;
    unsigned int wordDiffABC;
    unsigned int wordE;

    auto startMachineWord = std::chrono::high_resolution_clock::now();

    createMachineWord(A, strlen(A), wordA);
    createMachineWord(B, strlen(B), wordB);
    createMachineWord(C, strlen(C), wordC);
    createMachineWord(D, strlen(D), wordD);

    wordE = (wordA | (wordB & wordC)) | wordD;

    auto endMachineWord = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationMachineWord = endMachineWord - startMachineWord;
    std::cout << "Execution time for a machine word: " << durationMachineWord.count() << " seconds\n";

    printMachineWord(wordE);



    return 0;
}