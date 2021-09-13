#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <cctype>

bool have_digit(const std::string& str)
{
	for (const char ch : str)
	{
		if (isdigit(ch))
		{
			return true;
		}
	}

	return false;
}

int main(int argc, char *argv[])
{
	std::string file_name = "data.txt";
	std::ifstream file(file_name);

	std::vector<std::string> lines;

	int word_count = 0;
	int number_count = 0;

	char buf[1024];

	while (!file.eof())
	{
		file.getline(buf, 1024);

		lines.push_back(std::string(buf));

		std::istringstream tokens(buf);
		while (!tokens.eof())
		{
			std::string token;
			tokens >> token;

			if (have_digit(token))
			{
				++number_count;
			}
			else
			{
				++word_count;
			}
		}
	}

	for (const std::string &line : lines)
	{
		std::cout << line << std::endl;
	}

	std::cout << std::endl;

	std::cout << "word count: " << word_count << std::endl;
	std::cout << "number count: " << number_count << std::endl;
}