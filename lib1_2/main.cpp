#include <iostream>
#include <ostream>
#include <ctime>
#include <chrono>

#include "SetArray.h"
#include "setList.h"
#include "SetBoolArray.h"
#include "SetMachineWord.h"
#include "Generator.h"
#include "Globals.h"

int main() 
{
	srand(time(nullptr));
	int i = 0;
	SetArray Es;
	setList EList;
	SetBoolArray EBool;
	SetMachineWord EWord;

	std::cout << "Input power of set: ";
	std::cin >> powerOfSet;
	std::cout << std::endl;

	char* A = generateNumbers();
	char* B = generateNumbers();
	char* C = generateNumbers();
	char* D = generateNumbers();

	std::cout << "Set A: " << A << std::endl;
	std::cout << "Set B: " << B << std::endl;
	std::cout << "Set C: " << C << std::endl;
	std::cout << "Set D: " << D << std::endl << std::endl;


	SetArray As = SetArray(A);
	SetArray Bs = SetArray(B);
	SetArray Cs = SetArray(C);
	SetArray Ds = SetArray(D);
	auto startArray = std::chrono::high_resolution_clock::now();

	Es = (As | (Bs & Cs)) | Ds;

	auto endArray = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> durationArray = endArray - startArray;
	std::cout << "Execution time for array: " << durationArray.count() << " seconds\n";

	std::cout << "Result Array: " << Es << std::endl << std::endl << std::endl;



	setList AList = setList(A);
	setList BList = setList(B);
	setList CList = setList(C);
	setList DList = setList(D);

	auto startList = std::chrono::high_resolution_clock::now();

	EList = (AList | (BList & CList)) | DList;

	auto endList = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> durationList = endList - startList;
	std::cout << "Execution time for lists: " << durationList.count() << " seconds\n";

	std::cout << "Result List: " << EList << std::endl << std::endl << std::endl;



	SetBoolArray ABool = SetBoolArray(A);
	SetBoolArray BBool = SetBoolArray(B);
	SetBoolArray CBool = SetBoolArray(C);
	SetBoolArray DBool = SetBoolArray(D);

	auto startBitArray = std::chrono::high_resolution_clock::now();

	EBool = (ABool | (BBool & CBool)) | DBool;

	auto endBitArray = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> durationBitArray = endBitArray - startBitArray;
	std::cout << "Execution time for bit array: " << durationBitArray.count() << " seconds\n";

	std::cout << "Result Bit Array: " << EBool << std::endl << std::endl << std::endl;


	SetMachineWord AWord = SetMachineWord(A);
	SetMachineWord BWord = SetMachineWord(B);
	SetMachineWord CWord = SetMachineWord(C);
	SetMachineWord DWord = SetMachineWord(D);

	auto startMachineWord = std::chrono::high_resolution_clock::now();

	EWord = (AWord | (BWord & CWord)) | DWord;

	auto endMachineWord = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> durationMachineWord = endMachineWord - startMachineWord;
	std::cout << "Execution time for a machine word: " << durationMachineWord.count() << " seconds\n";

	std::cout << "Result Machine Word: " << EWord << std::endl;

	return 0;
}