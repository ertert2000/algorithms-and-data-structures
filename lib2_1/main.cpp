#include <iostream>
#include "Rectangle.h"
#include "Line.h"
#include "Shape.h"
#include "Screen.h"
#include "ShapeControl.h"
#include "Parallelogram.h"

// ПРИМЕР ДОБАВКИ: дополнительный фрагмент – полуокружность
class h_circle : public Rectangle, public Reflectable
{
protected:
	Screen& screen;
public:
	h_circle(Point a, int rd) : Rectangle(Point(a.x - rd, a.y), Point(a.x + rd, a.y + rd * 0.7 + 1)), screen(Screen::getInstance()) {}

	void draw();

	void flip_horisontally() {};   // Отразить горизонтально (пустая функция)

	void rotate_right() {}     // Повернуть вправо 

	void rotate_left() {}      // Повернуть влево

};

void h_circle::draw()   //Алгоритм Брезенхэма для окружностей
{  // (выдаются два сектора, указываемые значением reflected::vert)

	int x0 = (sw.x + ne.x) / 2, y0 = vert ? ne.y : sw.y;
	int radius = (ne.x - sw.x) / 2;
	int x = 0, y = radius, delta = 2 - 2 * radius, error = 0;

	while (y >= 0) // Цикл рисования 
	{
		if (vert)
		{
			screen.put_point(x0 + x, y0 - y * 0.7);
			screen.put_point(x0 - x, y0 - y * 0.7);
		}
		else
		{
			screen.put_point(x0 + x, y0 + y * 0.7);
			screen.put_point(x0 - x, y0 + y * 0.7);
		}
		error = 2 * (delta + y) - 1;

		if (delta < 0 && error <= 0)
		{
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;

		if (delta > 0 && error > 0)
		{
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
	//	rectangle::draw();
}
// ПРИМЕР ДОБАВКИ: дополнительная функция присоединения…



void down(Shape& p, const Shape& q)
{
	Point n = q.south();
	Point s = p.north();
	p.move(n.x - s.x, n.y - s.y - 1);
}

// Cборная пользовательская фигура – физиономия
class myshape : public Rectangle
{   // Моя фигура ЯВЛЯЕТСЯ

	int w, h;			             //        прямоугольником
	Line l_eye;    // левый глаз – моя фигура СОДЕРЖИТ линию
	Line r_eye;   // правый глаз
	Line mouth;  // рот
	Screen& screen;

public:
	myshape(Point, Point);

	void draw();

	void move(int, int);

	void resize(double r) { Rectangle::resize(r); Rectangle::move(w * (1 - r) * 0.5, h * (1 - r) * 0.5); }

	void rotate_left() {}

	void rotate_right() {}
};

myshape::myshape(Point a, Point b) : Rectangle(a, b),	//Инициализация базового класса
w(neast().x - swest().x + 1), // Инициализация данных
h(neast().y - swest().y + 1), // – строго в порядке объявления!

l_eye(Point(swest().x + 2, swest().y + h * 3 / 4), 2),
r_eye(Point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
mouth(Point(swest().x + 2, swest().y + h / 4), w - 4), 
screen(Screen::getInstance())
{}

void myshape::draw()
{
	Rectangle::draw();      //Контур лица (глаза и нос рисуются сами!) 
	int a = (swest().x + neast().x) / 2;
	int b = (swest().y + neast().y) / 2;

	screen.put_point(Point(a, b));   // Нос – существует только на рисунке!
}

void myshape::move(int a, int b)
{
	Rectangle::move(a, b);
	l_eye.move(a, b);
	r_eye.move(a, b);
	mouth.move(a, b);
}

void up(Shape& p, const Shape& q);


void upM(Shape& p, const Shape& q, int y_offset = 1, bool center = true)
{
	Point n = q.north();
	Point s = p.south();

	int dy = n.y - s.y - y_offset + 9;

	int dx = 0;
	if (center)
		dx = (n.x - s.x);

	p.move(dx, dy);
}

void rightS(Shape& p, const Shape& q)
{
	Point bottomRight = q.seast();

	Point pWest = p.west();

	int dx = bottomRight.x - pWest.x;
	int dy = bottomRight.y - pWest.y;

	p.move(dx, dy - 3);
}

void leftS(Shape& p, const Shape& q)
{
	Point bottomRight = q.swest();

	Point pWest = p.east();

	int dx = bottomRight.x - pWest.x;
	int dy = bottomRight.y - pWest.y;

	p.move(dx, dy - 3);
}

int main()
{
	Screen& screen = Screen::getInstance();
	ShapeControl shapeControl;

	//== 1. Объявление набора фигур ==
	Parallelogram p(Point(5, 5), Point(15, 5), Point(20, 15), Point(10, 15));
	Parallelogram b1(Point(5, 5), Point(15, 5), Point(20, 15), Point(10, 15));
	Parallelogram b2(Point(5, 5), Point(15, 5), Point(20, 15), Point(10, 15));

	p.move(10, 20);
	b1.move(40, 20);
	b2.move(25, 30);

	Rectangle hat(Point(0, 0), Point(14, 5));
	Line brim(Point(20, 9), 17);

	myshape face(Point(15, 10), Point(27, 18));
	h_circle beard(Point(40, 10), 5);

	shapeControl.shape_refresh();

	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор

	//== 2. Подготовка к сборке ==
	p.flip_vertically();
	b1.flip_horisontally();
	hat.rotate_right();
	brim.resize(2.0);
	face.resize(1.2);
	b1.resize(0.7);
	b2.resize(0.7);
	beard.flip_vertically();
	beard.resize(1.2);

	shapeControl.shape_refresh();

	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений

	//== 3. Сборка изображения ==
	//	face.move(0, -10); // Лицо – в исходное положение (если нужно!)
	up(brim, face);
	up(hat, brim);
	upM(p, hat, false);
	down(beard, face);
	rightS(b2, face);
	leftS(b1, face);


	shapeControl.shape_refresh();

	std::cout << "=== Ready! ===\n";
	std::cin.get();       //Смотреть результат

	screen.screen_destroy();

	return 0;
}


void up(Shape& p, const Shape& q) // поместить фигуру p над фигурой q
{	//Это ОБЫЧНАЯ функция, не член класса! Динамическое связыва-ние!!
	Point n = q.north();
	Point s = p.south();

	p.move(n.x - s.x, n.y - s.y + 1);
}