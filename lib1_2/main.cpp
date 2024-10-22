#include <iostream>
#include <ostream>
#include "SetArray.h"

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

	return 0;
}


