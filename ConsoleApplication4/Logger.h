#pragma once
#include <sstream>      // std::stringstream
#include <iostream>

namespace logging
{
	#define Print = 1

		template<typename T>
		static void print(T&& str)
		{
#ifdef Print
			std::cout << str << "\n";
#endif
		}

		static void print(std::string str = "")
		{
#ifdef Print
			std::cout << str << "\n";
#endif
		}

		template<>
		static void print<std::stringstream>(std::stringstream&& str)
		{
#ifdef Print
			std::cout << str.str() << "\n";
#endif
		}


}
