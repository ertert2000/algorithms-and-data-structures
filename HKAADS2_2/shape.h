#include <list>
#include <stdexcept>
#include <iostream>
using std::list;
using namespace std;
//==1. ��������� ������ � ����� ������� �������� ==
char screen[XMAX][YMAX];

enum color
{
	black = '*',
	white = '.'
};

void screen_init()
{
	for (int i = 0; i < XMAX; i++)
		for (int j = 0; j < YMAX; j++)
			screen[i][j] = white;
}

void screen_destroy()
{
	for (int i = 0; i < XMAX; i++)
		for (int j = 0; j < YMAX; j++)
			screen[i][j] = black;
}

bool on_screen(int x, int y)
{
	return (x >= 0 && x < XMAX && y >= 0 && y < YMAX);
}

void put_point(int x, int y)
{
	if (!on_screen(x, y))
		throw std::out_of_range("Point is out of screen bounds");

	screen[x][y] = black;
}

void put_line(int x0, int y0, int x1, int y1)
{
	if (!on_screen(x0, y0) || !on_screen(x1, y1))
		throw std::out_of_range("Line is out of screen bounds");

	int dx = (x1 >= x0) ? 1 : -1;
	int dy = (y1 >= y0) ? 1 : -1;
	int a = abs(x1 - x0);
	int b = abs(y1 - y0);

	int two_a = a << 1;
	int two_b = b << 1;
	int x_crit = two_a - b;
	int err = 0;

	while (true)
	{
		try
		{
			put_point(x0, y0);
		}
		catch (std::out_of_range)
		{
			std::cerr << "Line is out of screen bounds" << std::endl;
			break;
		}

		if (x0 == x1 && y0 == y1) break;

		if (err <= x_crit) err += two_b, x0 += dx;
		if (err >= a || a < b) err -= two_a, y0 += dy;
	}
}

void screen_clear()
{
	screen_init();
}

void screen_refresh()
{
	for (int i = 0; i < XMAX; i++)
	{
		for (int j = 0; j < YMAX; j++)
			cout << screen[i][j];
		cout << '\n';
	}
}

struct shape
{
	static list<shape*> shapes;
	shape() { shapes.push_back(this); }
	virtual ~shape() { shapes.remove(this); }

	virtual point north() const = 0;
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual point get_center() const = 0;
	virtual void draw() = 0;
	virtual void move(int, int) = 0;
	virtual void resize(double) = 0;
};

list<shape*> shape::shapes;

void shape_refresh()
{
	screen_clear();
	for (auto it = shape::shapes.begin(); it != shape::shapes.end(); ++it)
		(*it)->draw();
	screen_refresh();
}

class rotatable : virtual public shape
{
public:
	virtual void rotate_left() = 0;
	virtual void rotate_right() = 0;
};

class reflectable : virtual public shape
{
public:
	virtual void flip_horisontally() = 0;
	virtual void flip_vertically() = 0;
};

class line : public shape
{
protected:
	point w, e;
public:
	line(point a, point b) : w(a), e(b) 
	{
		if (!on_screen(a.x, a.y) || !on_screen(b.x, b.y))
			throw std::out_of_range("Line endpoints are out of screen bounds");
	}

	line(point a, int L) : w(a), e(point(a.x + L - 1, a.y)) 
	{
		if (!on_screen(a.x, a.y) || !on_screen(a.x + L - 1, a.y))
			throw std::out_of_range("Line endpoints are out of screen bounds");
	}

	point north() const { return point(w.x, (w.y + e.y) / 2); }
	point south() const { return point(w.x, (w.y + e.y) / 2); }
	point east() const { return point(max(w.x, e.x), (w.y + e.y) / 2); }
	point west() const { return point(min(w.x, e.x), (w.y + e.y) / 2); }
	point get_center() const { return point((w.x + e.x) / 2, (w.y + e.y) / 2); }
	point neast() const { return e; }
	point seast() const { return w; }
	point nwest() const { return w; }
	point swest() const { return e; }

	void move(int dx, int dy) 
	{ 
		if (!on_screen(w.x + dx, w.y + dy) || !on_screen(e.x + dx, e.y + dy))
			throw std::out_of_range("Line.move(): moving rectangle out of screen");

		w.x += dx; w.y += dy; e.x += dx; e.y += dy; 
	}
	void draw() 
	{ 
		try
		{
			put_line(w.x, w.y, e.x, e.y); 
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Up(): is out of screen bounds" << e.what() << std::endl;
		}
	}

	void resize(double d)
	{
		int center_x = (w.x + e.x) / 2;
		int center_y = (w.y + e.y) / 2;
		int len = abs(w.y - e.y);
		w.y = center_y - len / 2 * d;
		e.y = center_y + len / 2 * d;
	}
};

class rectangle : public rotatable
{
protected:
	point sw, ne;
public:
	rectangle(point a, point b) : sw(a), ne(b) 
	{
		if (!on_screen(a.x, a.y) || !on_screen(b.x, b.y))
			throw std::out_of_range("Rectangle corners are out of screen bounds");
	}
	point north() const { return point(ne.x, (sw.y + ne.y) / 2); }
	point south() const { return point(sw.x, (sw.y + ne.y) / 2); }
	point east() const { return point((sw.x + ne.x) / 2, ne.y); }
	point west() const { return point((sw.x + ne.x) / 2, sw.y); }
	point get_center() const { return point((sw.x + ne.x) / 2, (sw.y + ne.y) / 2); }
	point neast() const { return ne; }
	point seast() const { return point(sw.x, ne.y); }
	point nwest() const { return point(ne.x, sw.y); }
	point swest() const { return sw; }

	void rotate_right()
	{
		int dx = sw.x - ne.x;
		int dy = ne.y - sw.y;
		int center_x = (sw.x + ne.x) / 2;
		int center_y = (sw.y + ne.y) / 2;
		sw.x = center_x + dy / 2;
		sw.y = center_y - dx / 2;
		ne.x = sw.x - dy;
		ne.y = sw.y + dx;
	}

	void rotate_left()
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		ne.x = sw.x + h * 2;
		ne.y = sw.y + w / 2;
	}

	void move(int dx, int dy)
	{
		if (!on_screen(sw.x + dx, sw.y + dy) || !on_screen(ne.x + dx, ne.y + dy))
			throw std::out_of_range("Rectangle.move(): moving rectangle out of screen");

		sw.x += dx;
		sw.y += dy;
		ne.x += dx;
		ne.y += dy;
	}

	void resize(double d)
	{
		if (d <= 0)
			throw std::out_of_range("Resize shape must be positive");

		ne.x = sw.x + (ne.x - sw.x) * d;
		ne.y = sw.y + (ne.y - sw.y) * d;
	}

	void draw()
	{
		try
		{
			put_line(sw.x, sw.y, ne.x, sw.y);
			put_line(ne.x, sw.y, ne.x, ne.y);
			put_line(ne.x, ne.y, sw.x, ne.y);
			put_line(sw.x, ne.y, sw.x, sw.y);
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Rectangle.draw(): is out of screen bounds" << e.what() << std::endl;
		}
	}
};

void up(shape& p, const shape& q)
{
	try
	{
		point n = q.north();
		point s = p.south();
		p.move(n.x - s.x - 1, n.y - s.y);
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Up(): is out of screen bounds" << e.what() << std::endl;
	}
}

void attach_centered(shape& p, const shape& q) {
	try
	{
		int dx = q.get_center().x - p.get_center().x;
		int dy = q.get_center().y - p.get_center().y;
		p.move(dx, dy);
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Attach_centered(): is out of screen bounds" << e.what() << std::endl;
	}
}
