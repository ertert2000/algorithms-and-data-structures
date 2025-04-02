#include "Screen.h"

void Screen::screen_init()
{
	for (auto y = 0; y < YMAX; ++y)
		for (auto& x : screen[y])
			x = white;
}

void Screen::screen_destroy()
{
	for (auto y = 0; y < YMAX; ++y)
		for (auto& x : screen[y])
			x = black;
}

bool Screen::on_screen(int a, int b) { return 0 <= a && a < XMAX && 0 <= b && b < YMAX; }

bool Screen::isWithinBounds(const Point& p)
{
	return on_screen(p.x, p.y);
}


void Screen::put_point(int a, int b)
{
	if (!isWithinBounds(Point(a, b)))
		throw std::out_of_range("put_point: Coordinates out of screen bounds");

	screen[b][a] = black;
}

void Screen::put_line(int x0, int y0, int x1, int y1)
{
	if (!on_screen(x0, y0) || !on_screen(x1, y1))
		throw std::out_of_range("put_line: Line endpoints out of screen bounds");

	int dx = 1;
	int a = x1 - x0;
	if (a < 0)
		dx = -1, a = -a;

	int dy = 1;
	int b = y1 - y0;
	if (b < 0)
		dy = -1, b = -b;

	int two_a = 2 * a;
	int two_b = 2 * b;
	int xcrit = -b + two_a;
	int eps = 0;

	for (;;) //������������ ������ ����� �� ������ 
	{
		try 
		{
			put_point(x0, y0);
		}
		catch (const std::exception& e) 
		{
			std::cerr << "Error: " << e.what() << '\n';
			return;
		}

		if (x0 == x1 && y0 == y1)
			break;

		if (eps <= xcrit)
			x0 += dx, eps += two_b;

		if (eps >= a || a < b)
			y0 += dy, eps -= two_a;
	}
}

void Screen::screen_clear() { screen_init(); } //������� ������

void Screen::screen_refresh() // ���������� ������
{
	for (int y = YMAX - 1; 0 <= y; --y) // � ������� ������ �� ������
	{
		for (auto x : screen[y])    // �� ������ ������� �� �������
			std::cout << x;

		std::cout << '\n';
	}
}

Screen& Screen::getInstance()
{
	static Screen instance;
	return instance;
}