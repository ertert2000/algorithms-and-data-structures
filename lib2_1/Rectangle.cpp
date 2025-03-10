#include "Rectangle.h"

Rectangle::Rectangle(Point a, Point b) : sw(a), ne(b), screen(Screen::getInstance()) {}

Point Rectangle::north() const { return Point((sw.x + ne.x) / 2, ne.y); }

Point Rectangle::south() const { return Point((sw.x + ne.x) / 2, sw.y); }

Point Rectangle::east() const { return Point(ne.x, (sw.y + ne.y) / 2); }

Point Rectangle::west() const { return Point(sw.x, (sw.y + ne.y) / 2); }

Point Rectangle::neast() const { return ne; }

Point Rectangle::seast() const { return Point(ne.x, sw.y); }

Point Rectangle::nwest() const { return Point(sw.x, ne.y); }

Point Rectangle::swest() const { return sw; }

void Rectangle::rotate_right()           // Поворот вправо относительно se
{
	int w = ne.x - sw.x, h = ne.y - sw.y; // (учитывается масштаб по осям)
	sw.x = ne.x - h * 2;
	ne.y = sw.y + w / 2;
}

void Rectangle::rotate_left() // Поворот влево относительно sw
{
	int w = ne.x - sw.x, h = ne.y - sw.y;
	ne.x = sw.x + h * 2;
	ne.y = sw.y + w / 2;
}

void Rectangle::move(int a, int b)
{
	sw.x += a;
	sw.y += b;
	ne.x += a;
	ne.y += b;
}

void Rectangle::resize(int d)
{
	ne.x = sw.x + (ne.x - sw.x) * d;
	ne.y = sw.y + (ne.y - sw.y) * d;
}

void Rectangle::resize(double d)
{
	ne.x = sw.x + (ne.x - sw.x) * d;
	ne.y = sw.y + (ne.y - sw.y) * d;
}

void Rectangle::draw()
{
	screen.put_line(nwest(), ne);
	screen.put_line(ne, seast());

	screen.put_line(seast(), sw);
	screen.put_line(sw, nwest());
}