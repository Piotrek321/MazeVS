#pragma once
#include "Map.h"
#include <random>
#include <cmath>
class MapBuilder
{
public:
	MapBuilder();
	~MapBuilder();

	template<typename FieldType>
	static void generateMap(Map<FieldType>& map);

	template<typename FieldType>
	void generateMapBorders(Map<FieldType>& map) {}

	template<typename FieldType>
	static void generateStart(Map<FieldType>& map);

	template<typename FieldType>
	static void generate_(Map<FieldType>& map);

};

template<typename FieldType>
void MapBuilder::generate_(Map<FieldType>& map)
{
	//LOOK AROUND
}


template<typename FieldType>
void MapBuilder::generateMap(Map<FieldType>& map)
{
	generateStart(map);
}


template<typename FieldType>
 void MapBuilder::generateStart(Map<FieldType>& map)
{

	// Seed with a real random value, if available
	std::random_device r;

	// Choose a random mean between 1 and 6
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist_width(0, map.getWidth() - 1);
	FieldType start;
	start.value = 'S';
	start.x = uniform_dist_width(e1);
	if (start.x == 0 || start.x == map.getWidth() - 1)
	{
		std::uniform_int_distribution<int> uniform_dist_height(0, map.getHeight() - 1);

		start.y = uniform_dist_height(e1);
	}
	else
	{
		std::uniform_int_distribution<int> uniform_dist_height(0, 1);

		start.y = uniform_dist_height(e1);
	}

	std::cout << "m_start_x: " << start.x << '\n';
	std::cout << "m_start_y: " << start.y << '\n';

	map.setStart(std::move(start));
}