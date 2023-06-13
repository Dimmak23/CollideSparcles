#pragma once

#include <iostream>
#include <limits>
#include <sstream>

class Utils
{
	public:
		static inline const unsigned int initial_width{ 640 };
		static inline const unsigned int initial_height{ 480 };
		static inline unsigned int _width{ Utils::initial_width };
		static inline unsigned int _height{ Utils::initial_height };
		static inline const unsigned int max_width{ 21504 };
		static inline const unsigned int max_height{ 5236 };

		static void parseWindowSize(int argc, char* argv[]);
		static void parseSingleItem(std::stringstream& input, const char* command, const std::string_view& command_name,
									unsigned int& size) noexcept;
};

inline void Utils::parseWindowSize(int argc, char* argv[])
{
	if (argc > 1 && argc < 4)
	{
		std::stringstream parser{};

		Utils::parseSingleItem(parser, argv[1], std::string("width"), Utils::_width);
		Utils::parseSingleItem(parser, argv[2], std::string("height"), Utils::_height);

		std::cout << Utils::_width << '\n';
		std::cout << Utils::_height << '\n';
	}
}

inline void Utils::parseSingleItem(std::stringstream& input, const char* command, const std::string_view& command_name,
								   unsigned int& size) noexcept
{
	unsigned int max_size{ command_name == "width" ? Utils::max_width : Utils::max_height };
	unsigned int initial_size{ command_name == "width" ? Utils::initial_width : Utils::initial_height };

	input.str("");
	input << command;
	try
	{
		// Prevent sending negative numbers
		if (std::stoi(input.str()) < 0)
		{
			std::cout << "[value of " << command_name
					  << " should be bigger then 0] "
						 "parsing negative value for "
					  << command_name << ": " << size << '\n';
			throw std::exception();
		}
		size = std::stoi(input.str());
		// We are about to instantiate application window with
		// normal modern screen resolution width and height
		// so let's prevent sending too big number
		// https://en.wikipedia.org/wiki/List_of_largest_video_screens
		if (size > max_size)
		{
			std::cout << "[value of " << command_name << " should less then " << max_size
					  << "] parsing value bigger then predefined application max for " << command_name << ": " << size
					  << '\n';
			throw std::exception();
		}
	}
	catch (const std::invalid_argument& invalid_type)
	{
		std::cout << "parsing text to " << command_name << ": " << invalid_type.what() << '\n';
		size = initial_size;
	}
	catch (const std::exception& integer_overflow)
	{
		size = initial_size;
		// std::cout << "[unsigned int max: " << std::numeric_limits<unsigned int>::max()
		//   << "] parsing and overflow unsigned integer for command_name: " << integer_overflow.what() << '\n';
	}
}
