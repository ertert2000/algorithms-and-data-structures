#include "Line.h"

Line::Line(Point a, Point b) : w(a), e(b), screen(Screen::getInstance()) {}

Line::Line(Point a, int L) : w(Point(a.x + L - 1, a.y)), e(a), screen(Screen::getInstance()) {}

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
	w.x += a; 
	w.y += b; 
	e.x += a; 
	e.y += b; 
}

void Line::draw() 
{ 
	screen.put_line(w, e); 
}

void Line::resize(double d)                // Изменение длины линии в (d) раз
{
	e.x = w.x + (e.x - w.x) * d;
	e.y = w.y + (e.y - w.y) * d;
}