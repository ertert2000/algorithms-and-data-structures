#pragma once

#include "Shape.h"
#include "Screen.h"

class Line : public Shape
{
	/* отрезок пр€мой ["w", "e"].
   north( ) определ€ет точку Ђвыше центра отрезка и так далеко
   на север, как сама€ его северна€ точкаї, и т. п. */
protected:
	Point w, e;
	Screen& screen;
public:
	Line(Point a, Point b); //ѕроизвольна€ лини€ (по двум точкам)
	Line(Point a, int L); //√оризонтальна€ лини€

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

