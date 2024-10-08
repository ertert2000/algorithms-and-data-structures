#pragma once
class SetArray
{
private:
	char* arr = new char[11];
public:
	SetArray(const char arr[]);

	SetArray();

	void printArray();
};

