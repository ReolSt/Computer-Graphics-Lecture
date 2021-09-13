#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <algorithm>

std::string replace_all(const std::string& str, const std::string& from, const std::string& to)
{
	std::string result = str;

	std::string::size_type pos = 0;
	std::string::size_type offset = 0;

	while ((pos = result.find(from, offset)) != std::string::npos)
	{
		result.replace(result.begin() + pos, result.begin() + pos + from.length(), to);
		offset = pos + to.length();
	}

	return result;
}

int main(int argc, char* argv[])
{
	std::string file_name = "data.txt";
	std::ifstream file(file_name);

	std::vector<std::string> lines;

	std::string delimiter = " ";

	char buf[1024];

	while (!file.eof())
	{
		file.getline(buf, 1024);

		lines.push_back(std::string(buf));
	}

	while (1)
	{
		std::cout << "Command: ";
		std::cin.getline(buf, 1024);

		std::istringstream tokens(buf);

		std::string command;
		tokens >> command;

		if (command == "d")
		{
			for (auto& line : lines)
			{
				std::reverse(line.begin(), line.end());
			}
		}
		else if (command == "e")
		{
			for (auto& line : lines)
			{
				if (delimiter == " ")
				{
					for (std::string::size_type i = 3; i < line.length(); i += 5)
					{
						line.insert(i, "**");
					}
				}
				else
				{
					line = replace_all(line, delimiter, "");
				}
			}

			delimiter = delimiter == " " ? "**" : " ";
		}
		else if (command == "f")
		{
			for (auto& line : lines)
			{
				std::istringstream tokens(line);

				std::string result;

				std::string::size_type pos;
				std::string token;
				while ((pos = line.find(delimiter)) != std:: string::npos)
				{
					token = line.substr(0, pos);
					std::reverse(token.begin(), token.end());

					result += token + delimiter;
					line.erase(0, pos + delimiter.length());
				}

				std::reverse(line.begin(), line.end());
				result += line;

				line = result;
			}
		}
		else if (command == "g")
		{
			std::string from;
			std::string to;

			tokens >> from;
			tokens >> to;

			for (auto& line : lines)
			{
				line = replace_all(line, from, to);
			}
		}
		else if (command == "h")
		{
			for (auto& line : lines)
			{
				std::string result;
				std::string::size_type line_length = line.length();
				for (std::string::size_type i = 0; i < line_length - i - 1; ++i)
				{
					if (line[i] != line[line_length - i - 1])
					{
						break;
					}

					result += line[i];
				}

				std::cout << line << ": " << ((result.length() > 0) ? result : "0") << std::endl;
			}
			continue;
		}
		else if (command == "q")
		{
			break;
		}
		else
		{
			std::cout << "Unknown command." << std::endl;
			continue;
		}

		for (const std::string& line : lines)
		{
			std::cout << line << std::endl;
		}
	}
}