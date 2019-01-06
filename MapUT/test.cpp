#include "pch.h"
#include "../snake/Map.h"

namespace
{
	const int width = 20;
	const int height = 20;
}

TEST(MapUT, TestCreatingMapGetters)
{
	Map<char> map{ height ,width,'#' };
	EXPECT_EQ(width, map.getWidth());
	EXPECT_EQ(height, map.getHeight());
	auto x = map.getStart();
	EXPECT_TRUE(true);
}