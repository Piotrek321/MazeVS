#pragma once
#include <sstream> 
#include <vector>
#include "Globals.h"
#include "Field.h"
using FieldType = Field;
class Map
{
public:

	Map(int height, int width);

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

	Field* getStart();
	Field getEnd() const;

	
	void setStart(Field&& start);

	
	void setEnd(Field&& end);

	int getHeight() const;
	int getWidth() const;

	std::vector<std::vector<Field>> m_board;

private:

	Field m_start;
	Field  m_end;
	int m_heigth;
	int m_width;
	Field m_border;
};


Map::Map(int height, int width) :m_heigth(height), m_width(width)
{
	//static_assert(std::is_base_of<FieldType, Field>::value, "FieldType must derive from Field");

	m_board = std::vector< std::vector<Field>>(height, std::vector<Field>(width, Field(borderSign)));
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (j == 0 || i == 0 || j == height - 1 || i == width - 1)
			{
				m_board[j][i].isBorder = true;
				m_board[j][i].value = 'X';
			}
			std::cout << "\n";
			m_board[j][i].x = i;
			m_board[j][i].y = j;
		}
	}

}


void Map::printMap()
{
	for (int j = 0; j < m_heigth; ++j)
	{
		for (int i = 0; i < m_width; ++i)
		{
			std::cout << m_board[j][i].value;
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


inline FieldType  Map::getEnd() const
{
	return m_end;
}


inline Field *  Map::getStart()
{
	return &m_start;
}



inline void Map::setStart(Field && start)
{
	m_start = start;
	m_board[m_start.y][m_start.x] = m_start;
}




inline void Map::setEnd(Field && end)
{
	m_end = end;
}


inline int Map::getHeight() const
{
	return m_heigth;
}


inline int Map::getWidth() const
{
	return m_width;
}
