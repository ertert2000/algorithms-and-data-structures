#include "Shape.h"

Point::Point(int x = 0, int y = 0) : x(x), y(y) {}

int Point::cross(const Point& other) const
{
	if (&other == nullptr)
		throw std::invalid_argument("Invalid point reference in cross product");

	return x * other.y - y * other.x;
}

std::list<Shape*> Shape::shapes;

Shape::Shape()
{
    try
    {
        shapes.push_back(this);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: Failed to add shape to list: " << e.what() << '\n';
    }
}

Shape::~Shape()
{
    try
    {
        shapes.remove(this);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: Failed to remove shape from list: " << e.what() << '\n';
    }
}

Rotatable::Rotatable(Rotation r) : state(r) {}

void Rotatable::rotate_left() 
{
    try
    {
        state = Rotation::Left;
    }
    catch (...)
    {
        throw std::runtime_error("Rotation failed");
    }
}

void Rotatable::rotate_right()
{
    try
    {
        state = Rotation::Right;
    }
    catch (...)
    {
        throw std::runtime_error("Rotation failed");
    }
}

Reflectable::Reflectable(bool h, bool v) : hor(h), vert(v) {}

void Reflectable::flip_horisontally() 
{
    try
    {
        hor = !hor;
    }
    catch (...)
    {
        throw std::runtime_error("Horizontal flip failed");
    }
}

void Reflectable::flip_vertically() 
{
    try
    {
        vert = !vert;
    }
    catch (...)
    {
        throw std::runtime_error("Vertical flip failed");
    }
}