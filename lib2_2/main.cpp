#include <iostream>
#include <memory>
#include "Rectangle.h"
#include "Line.h"
#include "Shape.h"
#include "Screen.h"
#include "ShapeControl.h"
#include "Parallelogram.h"

// ������ �������: �������������� �������� � ��������������
class h_circle : public Rectangle, public Reflectable
{
protected:
	Screen& screen;
public:
	h_circle(Point a, int rd) : Rectangle(Point(a.x - rd, a.y), Point(a.x + rd, a.y + rd * 0.7 + 1)), screen(Screen::getInstance()) {}

	void draw();

	void flip_horisontally() {};   // �������� ������������� (������ �������)

	void rotate_right() {}     // ��������� ������ 

	void rotate_left() {}      // ��������� �����

};

void h_circle::draw()   //�������� ���������� ��� �����������
{  // (�������� ��� �������, ����������� ��������� reflected::vert)

	int x0 = (sw.x + ne.x) / 2, y0 = vert ? ne.y : sw.y;
	int radius = (ne.x - sw.x) / 2;
	int x = 0, y = radius, delta = 2 - 2 * radius, error = 0;

	while (y >= 0) // ���� ��������� 
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
// ������ �������: �������������� ������� ��������������



void down(Shape& p, const Shape& q)
{
	Point n = q.south();
	Point s = p.north();
	p.move(n.x - s.x, n.y - s.y - 1);
}

// C������ ���������������� ������ � ����������
class myshape : public Rectangle
{   // ��� ������ ��������

	int w, h;			             //        ���������������
	Line l_eye;    // ����� ���� � ��� ������ �������� �����
	Line r_eye;   // ������ ����
	Line mouth;  // ���
	Screen& screen;

public:
	myshape(Point, Point);

	void draw();

	void move(int, int);

	void resize(double r) { Rectangle::resize(r); Rectangle::move(w * (1 - r) * 0.5, h * (1 - r) * 0.5); }

	void rotate_left() {}

	void rotate_right() {}
};

myshape::myshape(Point a, Point b) : Rectangle(a, b),	//������������� �������� ������
w(neast().x - swest().x + 1), // ������������� ������
h(neast().y - swest().y + 1), // � ������ � ������� ����������!

l_eye(Point(swest().x + 2, swest().y + h * 3 / 4), 2),
r_eye(Point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
mouth(Point(swest().x + 2, swest().y + h / 4), w - 4), 
screen(Screen::getInstance())
{}

void myshape::draw()
{
	Rectangle::draw();      //������ ���� (����� � ��� �������� ����!) 
	int a = (swest().x + neast().x) / 2;
	int b = (swest().y + neast().y) / 2;

	screen.put_point(Point(a, b));   // ��� � ���������� ������ �� �������!
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
	std::unique_ptr<Parallelogram> p;
	std::unique_ptr<Parallelogram> b1;
	std::unique_ptr<Parallelogram> b2;
	Screen& screen = Screen::getInstance();
	ShapeControl shapeControl;
	try
	{
		try
		{
			p = std::make_unique<Parallelogram>(Point(-5, 5), Point(15, 5), Point(20, 15), Point(10, 15));
		}
		catch (const ParallelogramException& e)
		{
			std::cerr << "Creation error p: " << e.what() << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Out Of Range error p: " << e.what() << std::endl;
		}

		try
		{
			b1 = std::make_unique<Parallelogram>(Point(5, 5), Point(15, 5), Point(20, 15), Point(10, 15));
		}
		catch (const ParallelogramException& e)
		{
			std::cerr << "Creation error b1: " << e.what() << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Out Of Range error p: " << e.what() << std::endl;
		}

		try
		{
			b2 = std::make_unique<Parallelogram>(Point(5, 5), Point(15, 5), Point(20, 15), Point(10, 15));
		}
		catch (const ParallelogramException& e)
		{
			std::cerr << "Creation error b2: " << e.what() << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Out Of Range error p: " << e.what() << std::endl;
		}


		if (p) p->move(10, 20);
		if (b1) b1->move(40, 20);
		if (b2) b2->move(25, 30);

		Rectangle hat(Point(0, 0), Point(14, 5));
		Line brim(Point(20, 9), 17);
		myshape face(Point(15, 10), Point(27, 18));
		h_circle beard(Point(40, 10), 5);

		shapeControl.shape_refresh();

		std::cout << "=== Generated... ===\n";
		std::cin.get();

		try
		{
			if (p) p->flip_vertically();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error flip_vertically(): " << e.what() << std::endl;
		}

		try
		{
			if (b1) b1->flip_horisontally();
			if (b1) b1->flip_horisontally();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error flip_horisontally(): " << e.what() << std::endl;
		}

		try
		{
			hat.rotate_right();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error rotate_right(): " << e.what() << std::endl;
		}

		try
		{
			brim.resize(2.0);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error resize(): " << e.what() << std::endl;
		}

		try
		{
			face.resize(1.2);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error resize(1.2): " << e.what() << std::endl;
		}

		try
		{
			if (b1) b1->resize(0.7);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error resize(0.7): " << e.what() << std::endl;
		}

		try
		{
			if (b2) b2->resize(0.7);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error resize(0.7): " << e.what() << std::endl;
		}

		try
		{
			beard.flip_vertically();
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error flip_vertically() (beard): " << e.what() << std::endl;
		}

		try
		{
			beard.resize(1.2);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error resize(1.2) (beard): " << e.what() << std::endl;
		}

		shapeControl.shape_refresh();
		std::cout << "=== Prepared... ===\n";
		std::cin.get();

		//== 3. Финальное расположение ==
		try
		{
			up(brim, face);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error up(brim, face): " << e.what() << std::endl;
		}

		try
		{
			up(hat, brim);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error up(hat, brim): " << e.what() << std::endl;
		}

		try
		{
			if (p) upM(*p, hat, false);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error upM(p, hat): " << e.what() << std::endl;
		}

		try
		{
			down(beard, face);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error down(beard, face): " << e.what() << std::endl;
		}

		try
		{
			if (b2) rightS(*b2, face);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error rightS(b2, face): " << e.what() << std::endl;
		}

		try
		{
			if (b1) leftS(*b1, face);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error leftS(b1, face): " << e.what() << std::endl;
		}

		shapeControl.shape_refresh();
		std::cout << "=== Ready! ===\n";
		std::cin.get();
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "Memory isolation error: " << e.what() << std::endl;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Runtime error: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "General exception: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown exception!" << std::endl;
	}

	screen.screen_destroy();

	return 0;
}


void up(Shape& p, const Shape& q) // ��������� ������ p ��� ������� q
{	//��� ������� �������, �� ���� ������! ������������ �������-���!!
	Point n = q.north();
	Point s = p.south();

	p.move(n.x - s.x, n.y - s.y + 1);
}