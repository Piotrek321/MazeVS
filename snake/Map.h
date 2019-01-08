#pragma once
#include <sstream> 
#include <vector>
#include "Field.h"

template<typename T>
class Map
{
public:

	Map(int height, int width, T border);

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

	Field<T> getStart() const;
	Field<T> getEnd() const;
	void setStart(Field<T>&& start);
	void setEnd(Field<T>&& end);

	int getHeight() const;
	int getWidth() const;

	std::vector< std::vector<T>> m_board;

private:
	Field<T> m_start;
	Field<T> m_end;
	int m_heigth;
	int m_width;
	T m_border;
};

template<typename T>
Map<T>::Map(int height, int width, T border) :m_heigth(height), m_width(width), m_border(border)
{
	m_board = std::vector< std::vector<T>>(height, std::vector<T>(width, m_border));
}

template<typename T>
void Map<T>::printMap()
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

template<typename T>
inline Field<T>  Map<T>::getEnd() const
{
	return m_end;
}

template<typename T>
inline Field<T>  Map<T>::getStart() const
{
	return m_start;
}

template<typename T>
inline void Map<T>::setStart(Field<T> && start)
{
	m_start = start;
	m_board[m_start.y][m_start.x] = m_start.value;
}

template<typename T>
inline void Map<T>::setEnd(Field<T> && end)
{
	m_end = end;
}

template<typename T>
inline int Map<T>::getHeight() const
{
	return m_heigth;
}

template<typename T>
inline int Map<T>::getWidth() const
{
	return m_width;
}
