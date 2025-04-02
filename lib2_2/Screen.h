#pragma once

#include <iostream>
#include <stdexcept>
#include "Shape.h"

class Screen
{
protected:
	static const int XMAX = 120;
	static const int YMAX = 50;
	char screen[YMAX][XMAX];
	enum color { black = '*', white = '.' };

public:
	static Screen& getInstance();

	void put_point(int x, int y);

	void put_point(Point p) { put_point(p.x, p.y); }

	void put_line(int, int, int, int);

	void put_line(Point a, Point b) { put_line(a.x, a.y, b.x, b.y); }

	void screen_init();

	void screen_destroy();

	void screen_refresh();

	void screen_clear();

	bool on_screen(int a, int b);

	bool isWithinBounds(const Point& p);
};

