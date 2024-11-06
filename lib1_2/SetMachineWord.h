#pragma once
#include <iostream>

class SetMachineWord
{
private:
	unsigned int word;
public:
	SetMachineWord();

	SetMachineWord(const char array[]);

	friend std::ostream& operator<<(std::ostream& sys, const SetMachineWord& SetList);

	static SetMachineWord processInput(SetMachineWord A, SetMachineWord B, SetMachineWord C, SetMachineWord D);

	//~SetMachineWord();
};

