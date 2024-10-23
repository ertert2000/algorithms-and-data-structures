#include <iostream>
#include <ostream>
#include "SetArray.h"
#include "setList.h"
#include "SetBoolArray.h"
#include "SetMachineWord.h"

int main() {
	int i = 0;
	char A[] = { '1', '2', '3', '4', '\0' };
	char B[] = { '1', '2', '3', '4', '\0' };
	char C[] = { '1', '2', '3', '4', '\0' };
	char D[] = { '1', '2', '3', '4', '\0' };

	SetArray As = SetArray(A);
	SetArray Bs = SetArray(B);
	SetArray Cs = SetArray(C);
	SetArray Ds = SetArray(D);

	std::cout << SetArray::processInput(As, Bs, Cs, Ds) << std::endl;

	setList AList = setList(A);
	setList BList = setList(B);
	setList CList = setList(C);
	setList DList = setList(D);

	std::cout << setList::processInput(AList, BList, CList, DList) << std::endl;

	SetBoolArray ABool = SetBoolArray(A);
	SetBoolArray BBool = SetBoolArray(B);
	SetBoolArray CBool = SetBoolArray(C);
	SetBoolArray DBool = SetBoolArray(D);

	std::cout << SetBoolArray::processInput(ABool, BBool, CBool, DBool) << std::endl;

	SetMachineWord AWord = SetMachineWord(A);
	SetMachineWord BWord = SetMachineWord(B);
	SetMachineWord CWord = SetMachineWord(C);
	SetMachineWord DWord = SetMachineWord(D);

	std::cout << SetMachineWord::processInput(AWord, BWord, CWord, DWord) << std::endl;

	return 0;
}