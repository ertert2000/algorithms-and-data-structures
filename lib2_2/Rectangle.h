#pragma once

#include "Shape.h"
#include "Screen.h"

class Rectangle : public Rotatable
{
protected:
	Point sw, ne;
	Screen& screen;

public:
	Rectangle(Point a, Point b);

	Point north() const;
	Point south() const;

	Point east() const;
	Point west() const;

	Point neast() const;
	Point seast() const;

	Point nwest() const;
	Point swest() const;

	void rotate_right();

	void rotate_left();

	void move(int a, int b);

	void resize(int d);

	void resize(double d);

	void draw();
};

