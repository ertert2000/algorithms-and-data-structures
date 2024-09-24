#include <iostream>
#include <random>

char* generateNumbers()
{
	std::random_device rnd;
	std::mt19937 gen(rnd());
	std::uniform_int_distribution<> dist(0, 9);


	for (int i = 0; i < 10; i++)
		std::cout << dist(gen) << " ";

	return nullptr;
}


