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
				os << cell.value;
			}
			os << "\n";
		}
		return os;
	}

	FieldType getStart() const;
	FieldType getEnd() const;

	template<typename T = FieldType>
	void setStart(T&& start);

	template<typename T = FieldType>
	void setEnd(T&& end);

	int getHeight() const;
	int getWidth() const;

	std::vector<std::vector<FieldType>> m_board;

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

	m_board = std::vector< std::vector<FieldType>>(height, std::vector<FieldType>(width, FieldType(m_border)));
	for (int i =0; i<width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (j == 0 || i == 0 || j == height - 1 || i == width - 1)
			{
				m_board[j][i].isBorder = true;
				m_board[j][i].value = 'X';
			}
			m_board[j][i].x = i;
			m_board[j][i].y = j;
		}
	}

}

template<typename FieldType>
void Map<FieldType>::printMap()
{
	for (int j = 0; j < m_heigth; ++j)
	{
		for (int i = 0; i < m_width; ++i)
		{
			std::cout  << m_board[j][i].value;
		}
		std::cout << "\n";
	}
	/*for (const auto & row : m_board)
	{
		for (const auto & cell : row)
		{
			std::cout << cell;
		}
		std::cout << "\n";
	}*/
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
