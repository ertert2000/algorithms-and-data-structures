#pragma once
#include <list>

class Point
{	//Точка на экране
public:
	int x, y; //ИНКАПСУЛЯЦИЯ

	Point(int x, int y);

	Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); } //писал я
	Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); } //писал я
	Point operator*(double factor) const { return Point(x * factor, y * factor); }
	Point operator/(double factor) const { return Point(x / factor, y / factor); }
};

class Shape
{
protected:
	static std::list<Shape*> shapes;       // Список фигур (один на все фигуры!)
	friend class ShapeControl;

public:
	Shape(); //Фигура присоединяется к списку

	virtual Point north() const = 0;  //Точки для привязки
	virtual Point south() const = 0;
	virtual Point east()  const = 0;
	virtual Point west()  const = 0;
	virtual Point neast() const = 0;
	virtual Point seast() const = 0;
	virtual Point nwest() const = 0;
	virtual Point swest() const = 0;

	virtual void draw() = 0;		//Рисование
	virtual void move(int, int) = 0;	//Перемещение
	virtual void resize(double) = 0;    	//Изменение размера

	virtual ~Shape(); //Деструктор
};

class Rotatable : virtual public Shape
{
protected:
	enum class Rotation { Left, No, Right };
	Rotation state;

public:
	Rotatable(Rotation r = Rotation::No);

	void rotate_left();
	void rotate_right();
};

class Reflectable : virtual public Shape
{
protected:
	bool hor, vert;
public:
	Reflectable(bool h = false, bool v = false);

	void flip_horisontally();
	void flip_vertically();
};