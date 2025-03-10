#pragma once

#include "Screen.h"

class ShapeControl
{
protected:
	Screen& screen;
public:
	ShapeControl();

	void shape_refresh();    // Перерисовка всех фигур на экране
};

