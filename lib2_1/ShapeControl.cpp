#include "ShapeControl.h"

ShapeControl::ShapeControl() : screen(Screen::getInstance()) {}

void ShapeControl::shape_refresh()
{
	screen.screen_clear();

	for (auto p : Shape::shapes)
		p->draw(); //Динамическое связывание!!!

	screen.screen_refresh();
}