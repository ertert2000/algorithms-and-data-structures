#include "SetMachineWord.h"
#include <string>

SetMachineWord::SetMachineWord()
{
	word = 0;
}

SetMachineWord::SetMachineWord(const char input[])
{
	this->word = 0;

	for (int i = 0; i < strlen(input); ++i)
		this->word |= 1 << (input[i] - '0');
}

SetMachineWord SetMachineWord::processInput(SetMachineWord A, SetMachineWord B, SetMachineWord C, SetMachineWord D)
{
	SetMachineWord res = SetMachineWord();
	res.word = (A.word | (B.word & C.word)) | D.word;

	return res;
}

std::ostream& operator<<(std::ostream& sys, const SetMachineWord& setMachineWord)
{
	for (int i = 0; i < 10; i++)
		if (setMachineWord.word & (1 << i))
			sys << static_cast<char>(i + '0');

	return sys;
}
