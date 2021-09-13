#include <iostream>
#include <sstream>
#include <fstream>

#include <random>

void rand_coordinates(int &x, int &y)
{
	static std::random_device device;
	static std::mt19937 generator(device());

	static std::uniform_int_distribution<int> distributionX(0, 800);
	static std::uniform_int_distribution<int> distributionY(0, 600);

	x = distributionX(generator);
	y = distributionY(generator);
}

struct Line
{
public:
	int x1, y1;
	int x2, y2;
};

struct Rectangle
{
public:
	int x1, y1;
	int x2, y2;
};

void setup_line(Line &l)
{
	rand_coordinates(l.x1, l.y1);
	rand_coordinates(l.x2, l.y2);
}

void setup_rectangle(Rectangle &r)
{
	rand_coordinates(r.x1, r.y1);
	rand_coordinates(r.x2, r.y2);
}

bool is_colliding(Line &l, Rectangle &r)
{
	int left = r.x1 > r.x2 ? r.x2 : r.x1;
	int right = r.x1 > r.x2 ? r.x1 : r.x2;

	int bottom = r.y1 > r.y2 ? r.y1 : r.y2;
	int top = r.y1 > r.y2 ? r.y2 : r.y1;

	if (l.x1 >= left && l.x1 <= right && l.y1 >= top && l.y1 <= bottom)
	{
		return true;
	}

	if (l.x2 >= left && l.x2 <= right && l.y2 >= top && l.y2 <= bottom)
	{
		return true;
	}

	return false;
}

bool move_line(Line& l, int dx, int dy)
{
	l.x1 += dx;
	l.x2 += dx;

	if (l.x1 < 0 || l.x1 > 800 || l.x2 < 0 || l.x2 > 800)
	{
		l.x1 -= dx;
		l.x2 -= dx;
		return false;
	}

	l.y1 += dy;
	l.y2 += dy;

	if (l.y1 < 0 || l.y1 > 600 || l.y2 < 0 || l.y2 > 600)
	{
		l.y1 -= dy;
		l.y2 -= dy;
		return false;
	}

	return true;
}

bool move_rectangle(Rectangle& r, int dx, int dy)
{
	r.x1 += dx;
	r.x2 += dx;

	if (r.x1 < 0 || r.x1 > 800 || r.x2 < 0 || r.x2 > 800)
	{
		r.x1 -= dx;
		r.x2 -= dx;
		return false;
	}

	r.y1 += dy;
	r.y2 += dy;

	if (r.y1 < 0 || r.y1 > 600 || r.y2 < 0 || r.y2 > 600)
	{
		r.y1 -= dy;
		r.y2 -= dy;
		return false;
	}

	return true;
}

int main(int argc, char *argv[])
{
	Line l = { 0, 0, 0, 0 };
	Rectangle r = { 0, 0, 0, 0 };

	setup_line(l);
	setup_rectangle(r);

	std::cout << "Input Shape Coordinate Values:" << std::endl;
	std::cout << "        Rect: " << "(" << r.x1 << ", " << r.y1 << ") (" << r.x2 << ", " << r.y2 << ")" << std::endl;
	std::cout << "        Line: " << "(" << l.x1 << ", " << l.y1 << ") (" << l.x2 << ", " << l.y2 << ")" << std::endl;

	char buf[1024];
	while (1)
	{
		std::cout << "Command: ";
		std::cin.getline(buf, 1024);

		std::istringstream tokens(buf);

		std::string command;
		tokens >> command;

		int dx = 50;
		int dy = 50;

		bool move_result = true;

		if (command == "w")
		{
			move_result = move_rectangle(r, 0, -dy);
		}
		else if (command == "a")
		{
			move_result = move_rectangle(r, -dx, 0);
		}
		else if (command == "s")
		{
			move_result = move_rectangle(r, 0, dy);
		}
		else if (command == "d")
		{
			move_result = move_rectangle(r, dx, 0);
		}
		else if (command == "i")
		{
			move_result = move_line(l, 0, -dy);
		}
		else if (command == "j")
		{
			move_result = move_line(l, -dx, 0);
		}
		else if (command == "k")
		{
			move_result = move_line(l, 0, dy);
		}
		else if (command == "l")
		{
			move_result = move_line(l, dx, 0);
		}
		else if (command == "q")
		{
			break;
		}
		else
		{
			std::cout << "Unknown Command." << std::endl;
			continue;
		}

		if (!move_result)
		{
			std::cout << "Invaild movement!" << std::endl;
			continue;
		}

		std::cout << "        Rect: " << "(" << r.x1 << ", " << r.y1 << ") (" << r.x2 << ", " << r.y2 << ")" << std::endl;
		std::cout << "        Line: " << "(" << l.x1 << ", " << l.y1 << ") (" << l.x2 << ", " << l.y2 << ")" << std::endl;

		if (is_colliding(l, r))
		{
			std::cout << "Rectangle  & Line collide!!" << std::endl;
		}
	}
}