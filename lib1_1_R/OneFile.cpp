#include <iostream>
#include <cstring>
#include <ctime>
#include <chrono>
#include <bitset>
#include <random>
#include <set>


#define MAXSIZE 11

typedef struct Set
{
    char value;
    struct Set* next;
}Set;

int powerOfSet;

Set* init(char value)
{
    Set* node = (Set*)malloc(sizeof(Set));
    if (!(node))
        exit(1);
    node->value = value;

    node->next = NULL;
}

void addFront(Set*& Cola, char value)
{
    Set* temp = init(value);
    if (Cola == NULL)
    {
        Cola = temp;
        return;
    }
    Set* tmp = Cola;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = temp;

}

bool existsInList(Set* head, char data)
{
    Set* temp = head;
    while (temp != nullptr)
    {
        if (temp->value == data)
            return true;

        temp = temp->next;
    }
    return false;
}

void combineLists(Set*& E, Set* A, Set* B, Set* C, Set* D)
{
    Set* tempA = A;
    while (tempA != nullptr)
    {
        addFront(E, tempA->value);
        tempA = tempA->next;
    }

    Set* tempB = B;
    while (tempB != nullptr)
    {
        if (existsInList(C, tempB->value) && !existsInList(E, tempB->value))
            addFront(E, tempB->value);

        tempB = tempB->next;
    }

    Set* tempD = D;
    while (tempD != nullptr)
    {
        if (!existsInList(E, tempD->value))
            addFront(E, tempD->value);

        tempD = tempD->next;
    }
}

void printList(Set* head)
{
    Set* temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->value;
        temp = temp->next;
    }
}



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



const int universeSize = 10;


void createSet(const char A[], bool bitA[])
{
    for (int i = 0; i < universeSize; i++)
        bitA[i] = false;

    for (int i = 0; i < powerOfSet; i++)
    {
        int index = A[i] - '0';
        bitA[index] = true;
    }
}

void setUnion(const bool setA[], const bool setB[], bool result[])
{
    for (int i = 0; i < universeSize; i++)
        result[i] = setA[i] || setB[i];

}

void setIntersection(const bool setA[], const bool setB[], bool result[])
{
    for (int i = 0; i < universeSize; i++)
        result[i] = setA[i] && setB[i];

}

void processInputBit(const char A[], const char B[], const char C[], const char D[], char E[], int& sizeOutputArr)
{
    bool bitA[universeSize], bitB[universeSize], bitC[universeSize], bitD[universeSize];
    bool tempBC[universeSize], tempABC[universeSize];

    createSet(A, bitA);
    createSet(B, bitB);
    createSet(C, bitC);
    createSet(D, bitD);

    setIntersection(bitB, bitC, tempBC);

    setUnion(bitA, tempBC, tempABC);

    setUnion(tempABC, bitD, tempABC);

    sizeOutputArr = 0;
    for (int i = 0; i < universeSize; i++)
        if (tempABC[i])
            E[sizeOutputArr++] = '0' + i;

    E[sizeOutputArr] = '\0';
}

void createMachineWord(char array[], int len, unsigned int& result)
{
    result = 0;
    for (int i = 0; i < len; ++i)
        result |= 1 << (array[i] - '0');
}

void printMachineWord(unsigned int word)
{
    for (int i = 0; i < 10; i++)
        if (word & (1 << i))
            std::cout << static_cast<char>(i + '0');

    std::cout << std::endl;
}

char* generateNumbers()
{
    char* result = new char[11] {0};
    std::set<int> uniqueNumbers;
    std::random_device rnd;
    std::mt19937 gen(rnd());
    std::uniform_int_distribution<> dist(0, 9);

    while (uniqueNumbers.size() < powerOfSet)
    {
        int num = dist(gen);
        uniqueNumbers.insert(num);
    }

    int index = 0;
    for (int num : uniqueNumbers)
        result[index++] = '0' + num;

    return result;
}





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
    Set* structA = NULL;
    Set* structB = NULL;
    Set* structC = NULL;
    Set* structD = NULL;
    Set* structE = NULL;

    for (int i = 0; i < powerOfSet; i++)
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