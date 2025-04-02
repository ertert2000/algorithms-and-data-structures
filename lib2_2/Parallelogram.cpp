#include "Parallelogram.h"


Parallelogram::Parallelogram(Point a, Point b, Point c, Point d) : p1(a), p2(b), p3(c), p4(d), screen(Screen::getInstance()) 
{
    if (!screen.isWithinBounds(p1) || !screen.isWithinBounds(p2) || !screen.isWithinBounds(p3) || !screen.isWithinBounds(p4))
        throw ParallelogramException("One or more points are out of screen bounds");
    if ((p2 - p1).cross(p4 - p1) == 0)
        throw ParallelogramException("Points do not form a parallelogram");
}


Point Parallelogram::north() const { return (p1.y < p2.y && p1.y < p3.y && p1.y < p4.y) ? p1 : (p2.y < p3.y && p2.y < p4.y) ? p2 : (p3.y < p4.y) ? p3 : p4; }
Point Parallelogram::south() const { return (p1.y > p2.y && p1.y > p3.y && p1.y > p4.y) ? p1 : (p2.y > p3.y && p2.y > p4.y) ? p2 : (p3.y > p4.y) ? p3 : p4; }
Point Parallelogram::east() const { return (p1.x > p2.x && p1.x > p3.x && p1.x > p4.x) ? p1 : (p2.x > p3.x && p2.x > p4.x) ? p2 : (p3.x > p4.x) ? p3 : p4; }
Point Parallelogram::west() const { return (p1.x < p2.x && p1.x < p3.x && p1.x < p4.x) ? p1 : (p2.x < p3.x && p2.x < p4.x) ? p2 : (p3.x < p4.x) ? p3 : p4; }

Point Parallelogram::neast() const { return (p1.x > p2.x && p1.y < p2.y) ? p1 : (p2.x > p3.x && p2.y < p3.y) ? p2 : p3; }
Point Parallelogram::seast() const { return (p1.x > p2.x && p1.y > p2.y) ? p1 : (p2.x > p3.x && p2.y > p3.y) ? p2 : p3; }
Point Parallelogram::nwest() const { return (p1.x < p2.x && p1.y < p2.y) ? p1 : (p2.x < p3.x && p2.y < p3.y) ? p2 : p3; }
Point Parallelogram::swest() const { return (p1.x < p2.x && p1.y > p2.y) ? p1 : (p2.x < p3.x && p2.y > p3.y) ? p2 : p3; }

void Parallelogram::draw() 
{
    try 
    {
        screen.put_line(p1.x, p1.y, p2.x, p2.y);
        screen.put_line(p2.x, p2.y, p3.x, p3.y);
        screen.put_line(p3.x, p3.y, p4.x, p4.y);
        screen.put_line(p4.x, p4.y, p1.x, p1.y);
    }
    catch (const ParallelogramException& e)
    {
        std::cerr << "Drawing error: " << e.what() << std::endl;
    }
}

void Parallelogram::move(int dx, int dy) 
{
    Point new_p1 = p1 + Point(dx, dy);
    Point new_p2 = p2 + Point(dx, dy);
    Point new_p3 = p3 + Point(dx, dy);
    Point new_p4 = p4 + Point(dx, dy);

    if (!screen.isWithinBounds(new_p1) || !screen.isWithinBounds(new_p2) || !screen.isWithinBounds(new_p3) || !screen.isWithinBounds(new_p4))
        throw ParallelogramException("Moved parallelogram is out of screen bounds");

    p1 = new_p1;
    p2 = new_p2;
    p3 = new_p3;
    p4 = new_p4;
}

void Parallelogram::resize(double factor) {
    if (factor <= 0)
        throw ParallelogramException("Resize factor must be positive");

    p2 = p1 + (p2 - p1) * factor;
    p3 = p1 + (p3 - p1) * factor;
    p4 = p1 + (p4 - p1) * factor;
}

void Parallelogram::rotate_left() 
{
    if (state == Rotation::Left)
        throw ParallelogramException("Parallelogram has already been rotated");

    Point center = (p1 + p2 + p3 + p4) / 4;
    p1 = center + Point(-(p1.y - center.y), p1.x - center.x);
    p2 = center + Point(-(p2.y - center.y), p2.x - center.x);
    p3 = center + Point(-(p3.y - center.y), p3.x - center.x);
    p4 = center + Point(-(p4.y - center.y), p4.x - center.x);
    state = Rotation::Left;
}

void Parallelogram::rotate_right() 
{
    if (state == Rotation::Right)
        throw ParallelogramException("Parallelogram has already been rotated");

    Point center = (p1 + p2 + p3 + p4) / 4;
    p1 = center + Point(p1.y - center.y, -(p1.x - center.x));
    p2 = center + Point(p2.y - center.y, -(p2.x - center.x));
    p3 = center + Point(p3.y - center.y, -(p3.x - center.x));
    p4 = center + Point(p4.y - center.y, -(p4.x - center.x));
    state = Rotation::Right;
}

void Parallelogram::flip_horisontally() 
{
    if (hor)
        throw ParallelogramException("Parallelogram has already been flipped");

    Point center = (p1 + p2 + p3 + p4) / 4;
    p1.x = 2 * center.x - p1.x;
    p2.x = 2 * center.x - p2.x;
    p3.x = 2 * center.x - p3.x;
    p4.x = 2 * center.x - p4.x;
    hor = true;
}

void Parallelogram::flip_vertically() 
{
    if (vert)
        throw ParallelogramException("Parallelogram has already been flipped");

    Point center = (p1 + p2 + p3 + p4) / 4;
    p1.y = 2 * center.y - p1.y;
    p2.y = 2 * center.y - p2.y;
    p3.y = 2 * center.y - p3.y;
    p4.y = 2 * center.y - p4.y;
    vert = true;
}