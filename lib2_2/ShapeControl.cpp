#include "ShapeControl.h"

ShapeControl::ShapeControl() : screen(Screen::getInstance()) {}

void ShapeControl::shape_refresh()
{
	screen.screen_clear();

	for (auto p : Shape::shapes)
		p->draw(); //������������ ����������!!!

	screen.screen_refresh();
}