#pragma once
#include <ostream>

class SetArray
{
private:
	char* arr = new char[11];

	int n = 0;
public:
	SetArray(const char* input);

	SetArray(const SetArray& other);

	SetArray();

	SetArray operator&(const SetArray& other) const;

	SetArray operator|(const SetArray& other) const;

	SetArray& operator=(const SetArray& other);

	friend std::ostream& operator<<(std::ostream& sys, const SetArray& setArray);

	~SetArray();
};

