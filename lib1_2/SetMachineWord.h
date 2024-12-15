#pragma once
#include <iostream>

class SetMachineWord
{
private:
	unsigned int word;
public:
	SetMachineWord();

	SetMachineWord(const char array[]);

	SetMachineWord(const SetMachineWord& other);

	SetMachineWord operator&(const SetMachineWord& B) const;

	SetMachineWord operator|(const SetMachineWord& B) const;

	friend std::ostream& operator<<(std::ostream& sys, const SetMachineWord& SetList);

	~SetMachineWord();
};

