#include "pch.h"
#include "../snake/Map.h"
#include "../snake/MapBuilder.h"
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
	auto board = std::vector< std::vector<Field>>(height, std::vector<Field>(width, Field(border)));
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (j == 0 || i == 0 || j == height - 1 || i == width - 1)
			{
				board[j][i].isBorder = true;
				board[j][i].value = 'X';
			}
		}
	}
	testing::internal::CaptureStdout();
	std::cout << map;
	std::string realOutput = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	for (const auto & brd : board)
	{
		for (const auto & field : brd)
		{
			std::cout << field.value;
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

//////////////////////////////////////////////////////////
/////////////////////// MapBuilder ///////////////////////
//////////////////////////////////////////////////////////


TEST(MapBuilderUT, TestCreateEmptyMapThenSetStartAndVerifyItsPositionXis2Yis1)
{
	Map<Field> map{ height ,width, border};
	Field field{2, 1, '@'};

	Field &leftField = map.m_board[1][1];
	Field &downField = map.m_board[2][2];
	Field &rightField = map.m_board[1][3];

	auto availableFields = MapBuilder::lookAround(map, field);
	std::cout << "&leftField: " <<  &leftField << "\n";
	std::cout << "downField: " << &downField << "\n";

	std::cout <<"&availableFields[0].get(): "<< &availableFields[0].get()<< "\n";
	std::cout << "&availableFields[1].get(): " << &availableFields[1].get() << "\n";

 EXPECT_EQ(&availableFields[0].get(), &downField);
 EXPECT_EQ(&availableFields[1].get(), &leftField);
 EXPECT_EQ(&availableFields[2].get(), &rightField);

}

TEST(MapBuilderUT, TestCreateEmptyMapThenSetStartAndVerifyItsPositionX0YIs0)
{
	Map<Field> map{ height ,width, border };
	Field field{ 0, 0, '@' };
	auto availableFields = MapBuilder::lookAround(map, field);

	EXPECT_EQ(availableFields.size(), 0);
}

TEST(MapBuilderUT, TestCreateEmptyMapThenSetStartAndVerifyItsPositionX1YIs1)
{
	Map<Field> map{ height ,width, border };
	Field field{ 1, 1, '@' };

	Field &downField = map.m_board[2][1];
	Field &rightField = map.m_board[1][2];

	auto availableFields = MapBuilder::lookAround(map, field);
	
	EXPECT_EQ(&availableFields[0].get(), &downField);
	EXPECT_EQ(&availableFields[1].get(), &rightField);
}

TEST(MapBuilderUT, TestCreateEmptyMapThenSetStartAndVerifyItsPositionX18YIs1)
{
	Map<Field> map{ height ,width, border };
	Field field{ 18, 1, '@' };

	Field &downField = map.m_board[2][18];
	Field &rightField = map.m_board[1][17];

	auto availableFields = MapBuilder::lookAround(map, field);

	EXPECT_EQ(&availableFields[0].get(), &downField);
	EXPECT_EQ(&availableFields[1].get(), &rightField);
}

TEST(MapBuilderUT, TestCreateEmptyMapThenSetStartAndVerifyItsPositionX18YIs18)
{
	Map<Field> map{ height ,width, border };
	Field field{ 18, 18, '@' };

	Field &upField = map.m_board[17][18];
	Field &leftField = map.m_board[18][17];

	auto availableFields = MapBuilder::lookAround(map, field);

	EXPECT_EQ(&availableFields[0].get(), &upField);
	EXPECT_EQ(&availableFields[1].get(), &leftField);
}

TEST(MapBuilderUT, TestCreateEmptyMapThenSetStartAndVerifyItsPositionX2YIs2)
{
	Map<Field> map{ height ,width, border };
	Field field{ 2, 2, '@' };

	Field &upField = map.m_board[1][2];
	Field &downField = map.m_board[3][2];
	Field &leftField = map.m_board[2][1];
	Field &rightField = map.m_board[2][3];

	auto availableFields = MapBuilder::lookAround(map, field);

	EXPECT_EQ(&availableFields[0].get(), &upField);
	EXPECT_EQ(&availableFields[1].get(), &downField);
	EXPECT_EQ(&availableFields[2].get(), &leftField);
	EXPECT_EQ(&availableFields[3].get(), &rightField);
}