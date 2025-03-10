#include "Shape.h"

Point::Point(int x = 0, int y = 0) : x(x), y(y) {}

std::list<Shape*> Shape::shapes;

Shape::Shape() { shapes.push_back(this); }

Shape::~Shape() { shapes.remove(this); }

Rotatable::Rotatable(Rotation r) : state(r) {}

void Rotatable::rotate_left() { state = Rotation::Left; }

void Rotatable::rotate_right() { state = Rotation::Right; }

Reflectable::Reflectable(bool h, bool v) : hor(h), vert(v) {}

void Reflectable::flip_horisontally() { hor = !hor; }

void Reflectable::flip_vertically() { vert = !vert; }