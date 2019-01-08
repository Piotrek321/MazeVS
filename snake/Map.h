#pragma once
#include <sstream> 
#include <vector>
#include "Field.h"
template<typename FieldType>
class Map
{
public:

	Map(int height, int width, char border);

	void printMap();

	friend std::ostream &operator << (std::ostream & os, const Map& mh)
	{
		for (const auto & row : mh.m_board)
		{
			for (const auto & cell : row)
			{
				os << cell;
			}
			os << "\n";
		}
		return os;
	}

	FieldType getStart() const;
	FieldType getEnd() const;

	template<typename T>
	void setStart(T&& start);

	template<typename T>
	void setEnd(T&& end);

	int getHeight() const;
	int getWidth() const;

	std::vector< std::vector<char>> m_board;

private:

	FieldType m_start;
	FieldType  m_end;
	int m_heigth;
	int m_width;
	char m_border;
};

template<typename FieldType>
Map<FieldType>::Map(int height, int width, char border) :m_heigth(height), m_width(width), m_border(border)
{
	static_assert(std::is_base_of<FieldType, Field>::value, "FieldType must derive from Field");
	m_board = std::vector< std::vector<char>>(height, std::vector<char>(width, m_border));
}
template<typename FieldType>
void Map<FieldType>::printMap()
{
	for (const auto & row : m_board)
	{
		for (const auto & cell : row)
		{
			std::cout << cell;
		}
		std::cout << "\n";
	}
}

template<typename FieldType>
inline FieldType  Map<FieldType>::getEnd() const
{
	return m_end;
}

template<typename FieldType>
inline FieldType  Map<FieldType>::getStart() const
{
	return m_start;
}

template<typename FieldType>
template<typename T>
inline void Map<FieldType>::setStart(T && start)
{
	m_start = start;
	m_board[m_start.y][m_start.x] = m_start.value;
}

template<typename FieldType>
template<typename T>
inline void Map<FieldType>::setEnd(T && end)
{
	m_end = end;
}

template<typename FieldType>
inline int Map<FieldType>::getHeight() const
{
	return m_heigth;
}

template<typename FieldType>
inline int Map<FieldType>::getWidth() const
{
	return m_width;
}
