

#include "lines.hpp"

int lines(const char* filenames[])
{
	int line_counter = 0;

	for (size_t i = 0; filenames[i] != nullptr; i++)
	{
		std::ifstream my_file(filenames[i]);
		if (my_file.is_open())
		{
			std::string test_string;
			while (std::getline(my_file,test_string))
			{
				line_counter++;
			}
		}
	}
	return line_counter;
}