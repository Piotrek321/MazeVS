#pragma once
#include <sstream> 
#include <vector>

template<typename T>
class Map
{
public:

	Map(int height, int width, T border);

	void printMap();

	friend std::ostream &operator << (std::ostream & os, const Map& mh)
	{
		for (const auto & row : mh.m_map)
		{
			for (const auto & cell : row)
			{
				os << cell;
			}
			os << "\n";
		}
		return os;
	}

private:
	int m_heigth;
	int m_width;
	int m_start_x;
	int m_start_y;
	int m_end_x;
	int m_end_y;
	T m_border;
	std::vector< std::vector<T>> m_map;
};

template<typename T>
Map<T>::Map(int height, int width, T border) :m_heigth(height), m_width(width), m_border(border)
{
	m_map = std::vector< std::vector<T>>(height, std::vector<T>(width));
}

template<typename T>
void Map<T>::printMap()
{
	for (const auto & row : m_map)
	{
		for (const auto & cell : row)
		{
			std::cout << cell;
		}
		std::cout << "\n";
	}
}
