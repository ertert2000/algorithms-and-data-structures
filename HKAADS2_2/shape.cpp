#include <locale.h>
#include <iostream>
#include <memory>
#include "screen.h"
#include "shape.h"

// ������������� �����
void down(shape& p, const shape& q) {
    point n = q.south();
    point s = p.north();
    p.move(n.x - s.x, n.y - s.y);
}

class ShapeError : public  std::exception
{
private:
    std::string message;
public:
    explicit ShapeError(const std::string& msg) : message(msg) {}

	const char* what() const noexcept override
	{
		return message.c_str();
	}
};

void validate_point(const point& p) 
{
    if (p.x < 0 || p.y < 0 || p.x >= XMAX || p.y >= YMAX)
        throw ShapeError("Point is out of screen bounds");
}

// �����
class crest : public reflectable {
private:
    point center;
    int edge;
    bool rotated = false;
    bool mirrored = false;

public:
    crest(point p, int e) : center(p), edge(e) 
    {
        if (e <= 0) 
            throw ShapeError("Invalid crest size");
		if (p.x < 0 || p.y < 0 || p.x >= XMAX || p.y >= YMAX)
			throw std::out_of_range("Crest center is out of screen bounds");

        validate_point(center);
    }

    point get_center() const { return center; }
    int get_edge() const { return edge; }
    point north() const { return point(center.x, center.y + edge); }
    point south() const { return point(center.x, center.y - edge); }
    point east() const { return point(center.x + edge, center.y); }
    point west() const { return point(center.x - edge, center.y); }
    point neast() const { return point(center.x + edge, center.y + edge); }
    point seast() const { return point(center.x + edge, center.y - edge); }
    point nwest() const { return point(center.x - edge, center.y + edge); }
    point swest() const { return point(center.x - edge, center.y - edge); }

    void move(int a, int b) override {
        if (!on_screen(center.x + a, center.y + b))
            throw std::out_of_range("Crest.move(): Moving rectangle out of screen bounds");

        center.x += a;
        center.y += b;
        validate_point(center);
    }

    void resize(double d) override 
    {
        if (d <= 0) 
            throw std::out_of_range("crest.resize(): out of screen");

        edge = static_cast<int>(edge * d);
    }

    void draw() override 
    {
        try
        {
            put_line(north(), south());
            put_line(west(), east());
        }
        catch (std::out_of_range& e)
        {
			std::cerr << "crest.draw(): " << e.what() << std::endl;
        }
    }

    void flip_horisontally() override 
    {
        if (mirrored) 
            throw ShapeError("Already mirrored");

        center.x = -center.x;
        mirrored = true;
    }

    void flip_vertically() override 
    {
        if (mirrored) 
            throw ShapeError("Already mirrored");

        center.y = -center.y;
        mirrored = true;
    }
};

// ������� ��� ����������� ��������� ����� ������������ ������ ���� �� �����������
crest mirror_eye(const crest& right_eye, int face_center_y) {
    try
    {
        int mirrored_y = 2 * face_center_y - right_eye.get_center().y;
        auto eye = crest(point(right_eye.get_center().x, mirrored_y), right_eye.get_edge());

        return eye;
    }
	catch (const ShapeError& e)
	{
		std::cerr << "mirror_eye(): " << e.what() << std::endl;
	}
    catch (const std::out_of_range& e)
    {
		std::cerr << "mirror_eye(): is out of range" << e.what() << std::endl;
    }
}


// ����������
class myshape : public rectangle {
private:
    int w, h, e;
    crest right_eye;
    line mouth;
    bool rotated = false;

public:
    myshape(point, point, int);
    void draw();
    void move(int, int);
    void resize(int) {}
    void rotate_right() override 
    {
        if (rotated) 
            throw ShapeError("Already rotated");

        rotated = true;
    }
};

myshape::myshape(point a, point b, int e)
    : rectangle(a, b),
    w(neast().y - swest().y),
    h(swest().x - neast().x),
    e(e),
    right_eye(point(north().x + 0.25 * h, east().y - 0.25 * w), e),
    mouth(point(swest().x - h / 5, swest().y + w / 4),
        point(seast().x - h / 5, seast().y - w / 4)) 
{
    if (w <= 0 || h <= 0) 
        throw ShapeError("Invalid shape dimensions");
}

void myshape::draw() 
{
    try
    {
        rectangle::draw();
        int a = (swest().x + neast().x) / 2;
        int b = (swest().y + neast().y) / 2;
        put_point(point(a, b));

        right_eye.draw();
        crest left_eye = mirror_eye(right_eye, get_center().y);
        left_eye.draw();
        mouth.draw();
	}
    catch (const ShapeError& e)
    {
        std::cerr << "myshape::draw(): " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "myshape::draw(): is out of range" << e.what() << std::endl;
    }
}

void myshape::move(int a, int b) {
    rectangle::move(a, b);
    right_eye.move(a, b);
    mouth.move(a, b);
}

int main() 
{
    screen_init();

    std::unique_ptr<rectangle> hat;
    std::unique_ptr<crest> emblem;
    std::unique_ptr<line> brim;
    std::unique_ptr<myshape> face;
    try
    {
        try
        {
            hat = std::make_unique <rectangle>(point(80, 90), point(50, 100));
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when creating 'hat': " << e.what() << std::endl;
        }

        try
        {
            emblem = std::make_unique <crest>(point(-35, 95), 10);
        }
        catch (const ShapeError& e)
        {
            std::cerr << "Error when creating 'emblem': " << e.what() << std::endl;
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when creating 'emblem': " << e.what() << std::endl;
        }

        try
        {
            brim = std::make_unique <line>(point(20, 40), point(20, 60));
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when creating 'brim': " << e.what() << std::endl;
        }

        try
        {
            face = std::make_unique <myshape>(point(60, 30), point(40, 60), 2);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when creating 'face': " << e.what() << std::endl;
        }

        shape_refresh();
        system("pause");
        std::cout << "=== Generated... ===\n";

        try
        {
            if(hat) hat -> rotate_right();
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Rotation error 'hat': " << e.what() << std::endl;
        }

        try
        {
            if (emblem) emblem->resize(0.2);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when changing size 'emblem': " << e.what() << std::endl;
        }

        try
        {
            if (emblem && hat) emblem->move(hat->west().x - emblem->get_center().x, hat->north().y - emblem->get_center().y);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when moving 'emblem': " << e.what() << std::endl;
        }

        try
        {
            if (face) face->move(-5, 30);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when moving 'face': " << e.what() << std::endl;
        }

        try
        {
            if(brim) brim->resize(2);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when changing size 'brim': " << e.what() << std::endl;
        }

        shape_refresh();
        system("pause");
        std::cout << "=== Prepared... ===\n";

        try
        {
            if(brim && face) up(*brim, *face);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when calling 'up(brim, face)': " << e.what() << std::endl;
        }

        try
        {
            if (hat && brim) up(*hat, *brim);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when calling 'up(hat, brim)': " << e.what() << std::endl;
        }

        try
        {
            if (emblem && hat) attach_centered(*emblem, *hat);
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range" << e.what() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error when attaching 'Emblem' to 'Hat': " << e.what() << std::endl;
        }

        shape_refresh();
        std::cout << "=== Ready! ===\n";
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Out of range" << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred!" << std::endl;
    }

    screen_destroy();
    system("pause");
    return 0;
}
