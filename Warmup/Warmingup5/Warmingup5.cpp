#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <array>

#include <algorithm>

struct Point
{
	int x = 0;
	int y = 0;
	int z = 0;
};

int get_unsquared_distance(Point p)
{
	return p.x * p.x + p.y * p.y + p.z * p.z;
}

bool compare(Point &a, Point &b)
{
	int da = get_unsquared_distance(a);
	int db = get_unsquared_distance(b);

	if (da > db)
	{
		return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	std::array<Point, 10> list = {};

	int bottom = 0;
	int top = 0;

	char buf[1024];

	bool s_toggle = false;
	while (1)
	{
		std::cout << "Command: ";
		std::cin.getline(buf, 1024);

		std::istringstream tokens(buf);

		std::string command;
		tokens >> command;

		if(command == "+")
		{
			int x, y, z;
			tokens >> x;
			tokens >> y;
			tokens >> z;

			Point n{ x, y, z };
			if (top < 10)
			{
				list[top] = n;
				top += 1;
			}
			else if (top == 10 && bottom > 0)
			{
				bottom -= 1;
				list[bottom] = n;
			}
		}
		else if (command == "-")
		{
			if (top > 0)
			{
				top -= 1;
			}
		}
		else if (command == "e")
		{
			int x, y, z;
			tokens >> x;
			tokens >> y;
			tokens >> z;

			Point n{ x, y, z };
			if (top < 10)
			{
				if (bottom == 0)
				{
					for (int i = top; i >= bottom; --i)
					{
						list[i + 1] = list[i];
					}
					list[bottom] = n;

					top += 1;
				}
				else
				{
					bottom -= 1;
					list[bottom] = n;
				}
			}
		}
		else if (command == "d")
		{
			if (bottom < top)
			{
				bottom += 1;
			}
		}
		else if (command == "l")
		{
			std::cout << "List Element Count: " << top - bottom << std::endl;
		}
		else if (command == "c")
		{
			top = 0;
			bottom = 0;
		}
		else if (command == "m")
		{
			int max_distance = 0;
			int max_distance_index = 0;
			for (int i = bottom; i < top; ++i)
			{
				int distance = get_unsquared_distance(list[i]);
				if (distance > max_distance)
				{
					max_distance = distance;
					max_distance_index = i;
				}
			}

			std::cout << "Farthest List Element: " << list[max_distance_index].x << " " << list[max_distance_index].y << " " << list[max_distance_index].z << std::endl;
		}
		else if (command == "n")
		{
			int min_distance = (int)1e9;
			int min_distance_index = 0;
			for (int i = bottom; i < top; ++i)
			{
				int distance = get_unsquared_distance(list[i]);
				if (distance < min_distance)
				{
					min_distance = distance;
					min_distance_index = i;
				}
			}

			std::cout << "Closest List Element: " << list[min_distance_index].x << " " << list[min_distance_index].y << " " << list[min_distance_index].z << std::endl;
		}
		else if (command == "s")
		{
			if (!s_toggle)
			{
				std::vector<Point> sorted;

				for (int i = bottom; i < top; ++i)
				{
					sorted.push_back(list[i]);
				}
				
				std::sort(sorted.begin(), sorted.end(), compare);

				for (int i = 9; i >= 0; --i)
				{
					std::cout << i << ": ";
					if (i < sorted.size())
					{
						std::cout << sorted[i].x << " " << sorted[i].y << " " << sorted[i].z;
					}
					std::cout << std::endl;
				}

				s_toggle = true;
				continue;
			}
			else
			{
				s_toggle = false;
			}
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

		for (int i = 9; i >= 0; --i)
		{
			std::cout << i << ": ";
			if (i >= bottom && i < top)
			{
				std::cout << list[i].x << " " << list[i].y << " " << list[i].z;
			}
			std::cout << std::endl;
		}
	}
}