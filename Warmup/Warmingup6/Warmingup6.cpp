#include <iostream>
#include <sstream>
#include <iomanip>

#include <string>
#include <random>

int map[50][50];

void reset(int map[][50])
{
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			map[i][j] = 0;
		}
	}
}

int get_random_action()
{
	static std::random_device device;
	static std::mt19937 generator(device());
	
	static std::poisson_distribution<int> distribution(2);
	
	return distribution(generator);
}

int main(int argc, char* argv[])
{
	char buf[1024];
	while (1)
	{
		std::cout << "Command: ";
		std::cin.getline(buf, 1024);

		std::istringstream tokens(buf);

		std::string command;
		tokens >> command;

		if (command == "r")
		{
			reset(map);

			int x = 0;
			int y = 0;
			map[0][0] = 1;

			int iteration_count = 1;
			int prev_action = -1;
			int action_repeat_count = 0;

			int action_minimum_limit[4] = { 1, 1, 1, 1 };

			int action_count[4] = { 0, 0, 0, 0 };
			while (x < 49 || y < 49)
			{
				int action = 0;
				int action_initialized = false;

				while (!action_initialized || action_repeat_count >= 5)
				{
					action = get_random_action();

					if (action == 0 && y == 0)
					{
						continue;
					}
					else if (action == 1 && x == 49)
					{
						continue;
					}
					else if (action == 2 && y == 49)
					{
						continue;
					}
					else if (action == 3 && x == 0)
					{
						continue;
					}

					action_initialized = true;

					if (prev_action == action)
					{
						++action_repeat_count;
					}
					else
					{
						prev_action = action;
						action_repeat_count = 0;
					}
				}

				action_count[action] += 1;

				if (action == 0)
				{
					y -= 1;
				}
				else if (action == 1)
				{
					x += 1;
				}
				else if (action == 2)
				{
					y += 1;
				}
				else if (action == 3)
				{
					x -= 1;
				}

				iteration_count += 1;
				map[y][x] = iteration_count;
			}

			std::cout << x << " " << y << std::endl;

			for (int i = 0; i < 4; ++i)
			{
				if (action_count[i] < action_minimum_limit[i])
				{
					continue;
				}
			}

			for (int i = 0; i < 50; ++i)
			{
				for (int j = 0; j < 50; ++j)
				{
					std::cout << std::setw(4) << map[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
		else if (command == "Q")
		{
			break;
		}
		else
		{
			std::cout << "Unknown Command." << std::endl;
		}
	}
}