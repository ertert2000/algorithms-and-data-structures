#include <iostream>
//#include <vector>
//#include <unordered_set>

void addArr(int*& E, int addVal, int& size)
{
	int* tmp = new int[size + 1];
	memcpy((void*)tmp, (const void*)E, sizeof(int) * size);

	tmp[size] = addVal;

	delete[] E;
	size++;

	E = tmp;
}

int comp(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int main()
{
	/*const int quantity = 4;

	int A[quantity]{ 2, 5, 4, 8 };
	int D[quantity]{ 5, 0, 7, 6 };
	int C[quantity]{ 1, 5, 9, 3 };
	int B[quantity]{ 9, 0, 5, 7 };

	std::vector<int> E;
	std::unordered_set<int> BSet(B, B + quantity);

	for (int i = 0; i < quantity; i++)
		E.push_back(A[i]);

	for (int i = 0; i < quantity; i++)
		if (BSet.find(C[i]) != BSet.end())
			E.push_back(C[i]);

	for (int i = 0; i < quantity; i++)
		E.push_back(D[i]);

	for (int i = 0; i < E.size(); i++)
		std::cout << E[i] << std::endl;*/

	//A U D U B ^ C = E


	int size = 0;
	const int quantity = 4;

	int A[quantity]{ 2, 5, 4, 8 };
	int D[quantity]{ 5, 0, 7, 6 };
	int C[quantity]{ 1, 5, 9, 3 };
	int B[quantity]{ 9, 0, 5, 7 };

	int* E = new int[quantity];

	for (int i = 0; i < quantity; i++)
		addArr(E, A[i], size);

	qsort(B, quantity, sizeof(int), comp);
	qsort(C, quantity, sizeof(int), comp);

	int i = 0, j = 0;
	while (i < quantity && j < quantity) 
	{
		if (B[i] == C[j]) 
		{
			addArr(E, B[i], size);
			while (i < quantity - 1 && B[i] == B[i + 1])
				i++;
			while (j < quantity - 1 && C[j] == C[j + 1])
				j++;
			i++;
			j++;
		}
		else if (B[i] < C[j])
			i++;
		else
			j++;
	}

	for (int i = 0; i < quantity; i++)
		addArr(E, D[i], size);

	for (int i = 0; i < size; i++)
		std::cout << E[i] << std::endl;

	delete[] E;
	return 0;
}