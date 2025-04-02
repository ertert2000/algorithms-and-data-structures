#include "Rectangle.h"

Rectangle::Rectangle(Point a, Point b) : sw(a), ne(b), screen(Screen::getInstance())
{
	if (!screen.on_screen(a.x, a.y) || !screen.on_screen(b.x, b.y))
		throw std::out_of_range("Rectangle constructor: One or both points are out of screen bounds");

	if (a.x > b.x || a.y > b.y)
		throw std::invalid_argument("Rectangle constructor: Incorrect point order (sw should be bottom-left, ne should be top-right)");
}

Point Rectangle::north() const { return Point((sw.x + ne.x) / 2, ne.y); }

Point Rectangle::south() const { return Point((sw.x + ne.x) / 2, sw.y); }

Point Rectangle::east() const { return Point(ne.x, (sw.y + ne.y) / 2); }

Point Rectangle::west() const { return Point(sw.x, (sw.y + ne.y) / 2); }

Point Rectangle::neast() const { return ne; }

Point Rectangle::seast() const { return Point(ne.x, sw.y); }

Point Rectangle::nwest() const { return Point(sw.x, ne.y); }

Point Rectangle::swest() const { return sw; }

void Rectangle::rotate_right()           // ������� ������ ������������ se
{
	int w = ne.x - sw.x, h = ne.y - sw.y;

	int new_sw_x = ne.x - h * 2;
	int new_ne_y = sw.y + w / 2;

	if (!screen.on_screen(new_sw_x, sw.y) || !screen.on_screen(ne.x, new_ne_y))
		throw std::out_of_range("rotate_right(): Rectangle goes out of screen bounds");

	sw.x = new_sw_x;
	ne.y = new_ne_y;
}

void Rectangle::rotate_left() // ������� ����� ������������ sw
{
	int w = ne.x - sw.x, h = ne.y - sw.y;

	int new_ne_x = sw.x + h * 2;
	int new_ne_y = sw.y + w / 2;

	if (!screen.on_screen(new_ne_x, ne.y) || !screen.on_screen(sw.x, new_ne_y))
		throw std::out_of_range("rotate_left(): Rectangle goes out of screen bounds");

	ne.x = new_ne_x;
	ne.y = new_ne_y;
}

void Rectangle::move(int a, int b)
{
	if (!screen.on_screen(sw.x + a, sw.y + b) || !screen.on_screen(ne.x + a, ne.y + b))
		throw std::out_of_range("move(): Moving rectangle out of screen bounds");

	sw.x += a;
	sw.y += b;
	ne.x += a;
	ne.y += b;
}

void Rectangle::resize(int d)
{
	if (d <= 0)
		throw std::invalid_argument("resize(): Scaling factor must be positive");

	int new_ne_x = sw.x + (ne.x - sw.x) * d;
	int new_ne_y = sw.y + (ne.y - sw.y) * d;

	if (!screen.on_screen(new_ne_x, new_ne_y))
		throw std::out_of_range("resize(): Resized rectangle out of screen bounds");

	ne.x = new_ne_x;
	ne.y = new_ne_y;
}

void Rectangle::resize(double d)
{
	if (d <= 0)
		throw std::invalid_argument("resize(): Scaling factor must be positive");

	int new_ne_x = sw.x + (ne.x - sw.x) * d;
	int new_ne_y = sw.y + (ne.y - sw.y) * d;

	if (!screen.on_screen(new_ne_x, new_ne_y))
		throw std::out_of_range("resize(): Resized rectangle out of screen bounds");

	ne.x = new_ne_x;
	ne.y = new_ne_y;
}

void Rectangle::draw()
{
	try 
	{
		screen.put_line(nwest(), ne);
		screen.put_line(ne, seast());
		screen.put_line(seast(), sw);
		screen.put_line(sw, nwest());
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error in draw(): " << e.what() << '\n';
	}
}