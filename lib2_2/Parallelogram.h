#pragma once

#include "Shape.h"
#include "Screen.h"
#include "ParallelogramException.h"

class Parallelogram : public Rotatable, public Reflectable
{
protected:
    Point p1, p2, p3, p4;
    Screen& screen;

public:
    Parallelogram(Point a, Point b, Point c, Point d);

    Point north() const override;
    Point south() const override; //    yolo work     0.5c
    Point east() const override; // ___________________|__________________ = 1c
    Point west() const override;

    Point neast() const override;
    Point seast() const override;
    Point nwest() const override;
    Point swest() const override;

    void draw() override;

    void move(int dx, int dy) override;

    void resize(double factor) override;

    void rotate_left();

    void rotate_right();

    void flip_horisontally();

    void flip_vertically();
};
