#include "pch.h"
#include "../snake/Map.h"
#include <iostream>
#include <fstream>
namespace
{
	const int width = 20;
	const int height = 20;
	char border = '#';
}

TEST(MapUT, TestCreatingMapGetters)
{
	Map<char> map{ height ,width, '#' };
	auto board = std::vector< std::vector<decltype(border)>>(height, std::vector<decltype(border)>(width, border));

	testing::internal::CaptureStdout();
	std::cout << map;
	std::string realOutput = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	for (const auto & brd : board)
	{
		for (const auto & field : brd)
		{
			std::cout << field;
		}
		std::cout << "\n";
	}
	std::string expectedOutput = testing::internal::GetCapturedStdout();



	EXPECT_EQ(realOutput, expectedOutput);
	EXPECT_EQ(width, map.getWidth());
	EXPECT_EQ(height, map.getHeight());
	}