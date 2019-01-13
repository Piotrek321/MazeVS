#pragma once
#include "Map.h"
#include <random>
#include "pch.h"
#include <optional>
#include <cmath>
class MapBuilder
{
public:
	MapBuilder() {}
	~MapBuilder() {};

	template<typename FieldType>
	static void generateMap(Map<FieldType>& map);

	template<typename FieldType>
	void generateMapBorders(Map<FieldType>& map) {}

	template<typename FieldType>
	static void generateStart(Map<FieldType>& map);

	template<typename FieldType>
	static void generate_(Map<FieldType>& map);

	template<typename FieldType>
	//static void  lookAround();//const Map<FieldType>& map, const FieldType& field);

	//One concern... maybe it would be better to have some other type of vector and then return vector which always has 4 elements
	// and then you can access it by vec[enum::UP] ?
	// i.e vector<optional<TYPE>> . Beause now it is harder to test. You have to remeber what the output of fc will be
	static std::vector<std::reference_wrapper<FieldType>> lookAround(Map<FieldType>& map, const FieldType& field)
	{
		std::vector<std::reference_wrapper<FieldType>> availableMoves;
		//auto f = map.getStart();
		//std::cout << "f.x " << f.x << " f.y " << f.y << "\n";
		auto lookUp = [&map,&field, &availableMoves]()
		{
			std::cout << "field.x " << field.x << " field.y " << field.y << "\n";
			if (field.y  <= 0 || map.m_board[field.y -1 ][field.x ].isBorder == true)
			{

			}
			else
			{
				std::cout << "Look up\n";
				availableMoves.push_back(std::ref(map.m_board[field.y - 1][field.x ]));
			}
		};

		auto lookDown = [&map, &field, &availableMoves]()
		{
			std::cout << "field.x " << field.x << " field.y " << field.y << "\n";

			if (field.y + 1 >= map.getHeight() || map.m_board[field.y +1 ][field.x ].isBorder == true)
			{

			}
			else
			{
				std::cout << "Look down\n";
				availableMoves.push_back(std::ref(map.m_board[field.y + 1][field.x]));
				std::cout << "std::addressof(availableMoves[0].get()): " << std::addressof(availableMoves[0].get()) << "\n";

			}
		};

		auto lookLeft = [&map, &field, &availableMoves]()
		{
			std::cout << "field.x " << field.x << " field.y " << field.y << "\n";

			if (field.x - 1 < 0|| map.m_board[field.y][field.x - 1].isBorder == true)
			{

			}
			else
			{
				std::cout << "Look left\n";

				availableMoves.push_back(std::ref(map.m_board[field.y][field.x - 1]));
			}
		};

		auto lookRight = [&map, &field, &availableMoves]()
		{
			std::cout << "field.x " << field.x << " field.y " << field.y << "\n";

			if (field.x + 1 >= map.getWidth() || map.m_board[field.y][field.x + 1 ].isBorder == true)
			{

			}
			else
			{
				std::cout << "Look right\n";

				availableMoves.push_back(std::ref(map.m_board[field.y][field.x + 1]));
			}
		};
		std::cout << "BEFORE LOOK UP\n";

		lookUp();
		lookDown();
		lookLeft();
		lookRight();

		return std::move(availableMoves);

	}


};
/*
template<typename FieldType>
static std::vector<std::reference_wrapper<FieldType>> lookAround(const Map<FieldType>& map, const FieldType& field)
{
	//auto lookUp = [&map,&field]()
	//{

		//map.m_board[field.y][field.x]
//	};
	//std::vector<FieldType> vec;
//	vec.push_back(map.m_board[0][0]);

}*/

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