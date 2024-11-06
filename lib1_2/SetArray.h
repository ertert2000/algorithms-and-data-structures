#pragma once
#include <ostream>

class SetArray
{
private:
	char* arr = new char[11];
public:
	SetArray(char arr[]);

	SetArray();

	friend std::ostream& operator<<(std::ostream& sys, const SetArray& setArray);

	static SetArray processInput(SetArray A, SetArray B, SetArray C, SetArray D);

	//~SetArray();
};

