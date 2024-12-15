#include "SetMachineWord.h"
#include <string>

SetMachineWord::SetMachineWord(){ word = 0; std::cout << "default constructor called" << std::endl; }

SetMachineWord::SetMachineWord(const char input[])
{
	this->word = 0;

	for (int i = 0; i < strlen(input); ++i)
		this->word |= 1 << (input[i] - '0');

	std::cout << "string constructor called" << std::endl;
}

SetMachineWord::SetMachineWord(const SetMachineWord& other) : word(other.word) { std::cout << "Set copy constructor called for Set " << std::endl; }

SetMachineWord SetMachineWord::operator&(const SetMachineWord& B) const
{
	SetMachineWord result;
	result.word = word & B.word;
	std::cout << "operator & called" << std::endl;
	return result;
}

SetMachineWord SetMachineWord::operator|(const SetMachineWord& B) const
{
	SetMachineWord result;
	result.word = word | B.word;
	std::cout << "operator | called" << std::endl;
	return result;
}

SetMachineWord::~SetMachineWord() { std::cout << "Machine word destructor called" << std::endl; }

std::ostream& operator<<(std::ostream& sys, const SetMachineWord& setMachineWord)
{
	for (int i = 0; i < 10; i++)
		if (setMachineWord.word & (1 << i))
			sys << static_cast<char>(i + '0');

	return sys;
}
