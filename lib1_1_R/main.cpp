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
    char E[MAXSIZE];
    char EBit[11];
    Set* structA = nullptr;
    Set* structB = nullptr;
    Set* structC = nullptr;
    Set* structD = nullptr;
    Set* structE = nullptr;


    std::cout << "Set A: " << A << std::endl;
    std::cout << "Set B: " << B << std::endl;
    std::cout << "Set C: " << C << std::endl;
    std::cout << "Set D: " << D << std::endl << std::endl;


    //Array
    auto startArray = std::chrono::high_resolution_clock::now();
    processInput(A, B, C, D, E, sizeOutputArr);

    auto endArray = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationArray = endArray - startArray;
    std::cout << "Execution time for array: " << durationArray.count() << " seconds\n";

    std::cout << "Result Array: ";
    std::cout << E;

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
    bool bitE[10];

    createSet(A, bitA);
    createSet(B, bitB);
    createSet(C, bitC);
    createSet(D, bitD);

    auto startBitArray = std::chrono::high_resolution_clock::now();
    processInputBit(bitA, bitB, bitC, bitD, bitE);

    auto endBitArray = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationBitArray = endBitArray - startBitArray;
    std::cout << "Execution time for bit array: " << durationBitArray.count() << " seconds\n";

    std::cout << "Result Bit Array: ";
    sizeOutputArr = 0;
    for (int i = 0; i < 10; i++)
        if (bitE[i])
            EBit[sizeOutputArr++] = '0' + i;

    EBit[sizeOutputArr] = '\0';

    std::cout << EBit;
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
    std::chrono::duration<double> durationMachineWord = endMachineWord - startMachineWord; //из документайии в секундах
    std::cout << "Execution time for a machine word: " << durationMachineWord.count() << " seconds\n";
    
    std::cout << "Result Machine Word: ";
    printMachineWord(wordE);





    //free memory
    delete A;
    delete B;
    delete C;
    delete D;
    delete structA;
    delete structB;
    delete structC;
    delete structD;
    return 0;
}