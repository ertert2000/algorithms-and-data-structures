#pragma once

#include "Shape.h"
#include <iostream>

class Screen
{
protected:
	static const int XMAX = 120;  //Размер экрана
	static const int YMAX = 50;
	char screen[YMAX][XMAX];
	enum color { black = '*', white = '.' };

public:
	static Screen& getInstance();
	// Набор утилит для работы с экраном
	void put_point(int a, int b);    // Вывод точки (2 варианта)

	void put_point(Point p) { put_point(p.x, p.y); } //ИНКАПСУЛЯЦИЯ

	void put_line(int, int, int, int); // Вывод линии (2 варианта)

	void put_line(Point a, Point b) { put_line(a.x, a.y, b.x, b.y); }//ИНКАПСУЛЯЦИЯ

	void screen_init();		// Создание экрана

	void screen_destroy();	// Удаление 

	void screen_refresh();	// Обновление

	void screen_clear();   // Очистка

	bool on_screen(int a, int b);
};

