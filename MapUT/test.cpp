#include "pch.h"
#include "../snake/Map.h"
#include <iostream>
#include <fstream>
namespace
{
	const int width = 20;
	const int height = 20;
	const int startX = 10;
	const int startY = 5;
	char border = '#';
}

TEST(MapUT, TestCreatingMapGetters)
{
	Map<Field> map{ height ,width, '#' };
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

TEST(MapUT, TestCreateEmptyMapThenSetStartAndVerifyItsPosition)
{
	Map<Field> map{ height ,width, '#' };
	Field field(startX, startY, '@');

	map.setStart(field);
	
	auto fieldToBeVerified = map.getStart();

	EXPECT_EQ(field.x, fieldToBeVerified.x);
	EXPECT_EQ(field.y, fieldToBeVerified.y);
}