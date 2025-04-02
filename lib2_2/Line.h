#pragma once

#include "Shape.h"
#include "Screen.h"

class Line : public Shape
{
	/* ������� ������ ["w", "e"].
   north( ) ���������� ����� ����� ������ ������� � ��� ������
   �� �����, ��� ����� ��� �������� �����, � �. �. */
protected:
	Point w, e;
	Screen& screen;
public:
	Line(Point a, Point b); //������������ ����� (�� ���� ������)
	Line(Point a, int L); //�������������� �����

	Point north() const;
	Point south() const;

	Point east() const;
	Point west() const;

	Point neast() const;
	Point seast() const;

	Point nwest() const;
	Point swest() const;

	void move(int a, int b);

	void draw();

	void resize(double d);

};

