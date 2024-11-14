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

	void addBack(char value);

	void clear();

	bool exists(char value) const;
public:
	setList();

	setList(const char input[]);

	setList(const setList& other);

	friend std::ostream& operator<<(std::ostream& sys, const setList& setArray);

	setList& operator=(const setList& other);

	setList operator&(const setList& other) const;

	setList operator|(const setList& other);


	~setList();
};

