const int XMAX = 85;  //������ ������
const int YMAX = 130;

class point 
{
public:
    int x, y;
    point(int a = 0, int b = 0) 
    {
        if (a < 0 || a >= XMAX || b < 0 || b >= YMAX)
            throw std::out_of_range("Point out of screen bounds");

        x = a;
        y = b;
    }
};
// ����� ������ ��� ������ � �������
void put_point(int a, int b);    // ����� ����� (2 ��������)
void put_point(point p) { put_point(p.x, p.y); } //
void put_line(int, int, int, int); // ����� ����� (2 ��������)
void put_line(point a, point b)
{
	put_line(a.x, a.y, b.x, b.y);
}
void screen_init();		// �������� ������
void screen_destroy();	// �������� 
void screen_refresh();	// ����������
void screen_clear();	           // ������