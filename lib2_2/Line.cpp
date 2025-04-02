#include "Line.h"

Line::Line(Point a, Point b) : w(a), e(b), screen(Screen::getInstance()) 
{
	if (!screen.on_screen(a.x, a.y) || !screen.on_screen(b.x, b.y))
		throw std::out_of_range("Line constructor: One or both points are out of screen bounds");
}

Line::Line(Point a, int L) : w(Point(a.x + L - 1, a.y)), e(a), screen(Screen::getInstance()) 
{
	if (L <= 0)
		throw std::invalid_argument("Line constructor: Length must be positive");

	if (!screen.on_screen(w.x, w.y) || !screen.on_screen(e.x, e.y))
		throw std::out_of_range("Line constructor: Line is out of screen bounds");
}

Point Line::north() const { return Point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }

Point Line::south() const { return Point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }

Point Line::east() const { return Point(e.x < w.x ? w.x : e.x, (w.y + e.y) / 2); }

Point Line::west() const { return Point(e.x < w.x ? e.x : w.x, (w.y + e.y) / 2); }

Point Line::neast() const { return Point(w.x < e.x ? e.x : w.x, e.y < w.y ? w.y : e.y); }

Point Line::seast() const { return Point(w.x < e.x ? e.x : w.x, e.y < w.y ? e.y : w.y); }

Point Line::nwest() const { return Point(w.x < e.x ? w.x : e.x, e.y < w.y ? w.y : e.y); }

Point Line::swest() const { return Point(w.x < e.x ? w.x : e.x, e.y < w.y ? e.y : w.y); }

void Line::move(int a, int b) 
{ 
	if (!screen.on_screen(w.x + a, w.y + b) || !screen.on_screen(e.x + a, e.y + b))
		throw std::out_of_range("move(): Moving line out of screen bounds");

	w.x += a; 
	w.y += b; 
	e.x += a; 
	e.y += b; 
}

void Line::draw() 
{ 
	try 
	{
		screen.put_line(w, e);
	}
	catch (const std::exception& e) 
	{
		std::cerr << "Error in draw(): " << e.what() << '\n';
	}
}

void Line::resize(double d)
{
	if (d <= 0)
		throw std::invalid_argument("resize(): Scaling factor must be positive");

	e.x = w.x + (e.x - w.x) * d;
	e.y = w.y + (e.y - w.y) * d;
}