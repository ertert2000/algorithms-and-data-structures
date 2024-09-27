#include "List.h"
#include "Array.h"
#include "BitArray.h"
#include "MachineWord.h"
#include "Generator.h"
#include "Globals.h"
#include <ctime>
#include <chrono>

const short MAXSIZE = 11;

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
    /*char A[6] = { '0', '1', '2', '3', '4', '5' };
    char B[6] = { '0', '1', '2', '3', '4', '5' };
    char C[6] = { '0', '1', '2', '3', '4', '5' };
    char D[6] = { '0', '1', '2', '3', '4', '5' };*/
    char E[MAXSIZE];
    char EBit[MAXSIZE];
    Set* structA = NULL;
    Set* structB = NULL;
    Set* structC = NULL;
    Set* structD = NULL;
    Set* structE = NULL;


    std::cout << "Set A: ";
    for(int i = 0; i < powerOfSet; i++)
        std::cout << A[i];
    std::cout << std::endl;
    std::cout << "Set B: ";
    for (int i = 0; i < powerOfSet; i++)
        std::cout << B[i];
    std::cout << std::endl;
    std::cout << "Set C: ";
    for (int i = 0; i < powerOfSet; i++)
        std::cout << C[i];
    std::cout << std::endl;
    std::cout << "Set D: ";
    for (int i = 0; i < powerOfSet; i++)
        std::cout << D[i];
    std::cout << std::endl;
    std::cout << std::endl;


    //Array
    auto startArray = std::chrono::high_resolution_clock::now();
    processInput(A, B, C, D, E, sizeOutputArr);

    auto endArray = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationArray = endArray - startArray;
    std::cout << "Execution time for array: " << durationArray.count() << " seconds\n";

    std::cout << "Result Array: ";
    for (int i = 0; i < sizeOutputArr; i++)
        std::cout << E[i];

    std::cout << std::endl;
    std::cout << std::endl;




    //List
   
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

    auto startList = std::chrono::high_resolution_clock::now();
    combineLists(structE, structA, structB, structC, structD);

    auto endList = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationList = endList - startList;
    std::cout << "Execution time for lists: " << durationList.count() << " seconds\n";

    std::cout << "Result List: ";
    printList(structE);

    std::cout << std::endl;
    std::cout << std::endl;



    //Bit Array
    bool bitA[10], bitB[10], bitC[10], bitD[10];

    createSet(A, bitA);
    createSet(B, bitB);
    createSet(C, bitC);
    createSet(D, bitD);

    auto startBitArray = std::chrono::high_resolution_clock::now();
    processInputBit(bitA, bitB, bitC, bitD, EBit, sizeOutputArrBit);

    auto endBitArray = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationBitArray = endBitArray - startBitArray;
    std::cout << "Execution time for bit array: " << durationBitArray.count() << " seconds\n";

    std::cout << "Result Bit Array: ";
    for (int i = 0; i < sizeOutputArrBit; i++)
        std::cout << EBit[i];

    std::cout << std::endl;
    std::cout << std::endl;




    //MachineWord
    unsigned int wordA;
    unsigned int wordB;
    unsigned int wordC;
    unsigned int wordD;
    unsigned int wordUnionAD;
    unsigned int wordDiffABC;
    unsigned int wordE;


    createMachineWord(A, strlen(A), wordA);
    createMachineWord(B, strlen(B), wordB);
    createMachineWord(C, strlen(C), wordC);
    createMachineWord(D, strlen(D), wordD);

    auto startMachineWord = std::chrono::high_resolution_clock::now();

    wordE = (wordA | (wordB & wordC)) | wordD;

    auto endMachineWord = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationMachineWord = endMachineWord - startMachineWord;
    std::cout << "Execution time for a machine word: " << durationMachineWord.count() << " seconds\n";

    std::cout << "Result Machine Word: ";
    printMachineWord(wordE);



    return 0;
}