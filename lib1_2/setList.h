#pragma once
#include <ostream>


class setList
{
private:
	struct List
	{
		char value;
		List* next = nullptr;
	};

	List* head;

	static List* init(char value);

    void addFront(List*& node, char value);

	static void addBack(List*& node, char value);

	static bool existsInList(List* head, char data);
public:
	setList();

	setList(const char input[]);

	friend std::ostream& operator<<(std::ostream& sys, const setList& setArray);

	static setList processInput(setList A, setList B, setList C, setList D);

};

