#include "SetArray.h"
#include <iostream>


SetArray::SetArray(const char arr[]) {
	int i = 0;
	while (arr[i] != '\0') {
		this->arr[i] = arr[i];
		i++;
	}
}

SetArray::SetArray() {
	int j = 0;
	for (int i = 48; i < 59; i++) {
		arr[j] = i;
		j++;
	}
	arr[j] = '\0';
}

void SetArray::printArray() {
	std::cout << arr;
}


