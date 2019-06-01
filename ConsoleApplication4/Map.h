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
	Field* getEnd();


	
	void setStart(Field&& start);

	
	void setEnd(Field&& end);

	int getHeight() const;
	int getWidth() const;

	std::vector<std::vector<Field>> m_board;

private:

	Field* m_start;
	Field* m_end;
	int m_heigth;
	int m_width;
	Field m_border;
};