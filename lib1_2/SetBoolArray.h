#pragma once
#include <ostream>
class SetBoolArray
{
private:
	bool* arr;
	const int universeSize = 10;
public:
	SetBoolArray();

	SetBoolArray(const char input[]);

	SetBoolArray operator||(const SetBoolArray& other);

	SetBoolArray operator&&(const SetBoolArray& other);

	friend std::ostream& operator<<(std::ostream& sys, const SetBoolArray& SetList);

	static SetBoolArray processInput(SetBoolArray bitA, SetBoolArray bitB, SetBoolArray bitC, SetBoolArray bitD);

	//~SetBoolArray();
};

