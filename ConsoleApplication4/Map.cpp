#include "Map.h"
#include "Modifier.h"

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
				m_board[j][i].value = borderSign;
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
			if (startSign == m_board[j][i].value)
			{
				std::cout << m_board[j][i].value;
				//std::cout << Color::FG_RED << m_board[j][i].value << Color::FG_DEFAULT;
			}
			else if (startSign == m_board[j][i].value)
			{
				std::cout << Color::FG_BLUE << m_board[j][i].value << Color::FG_DEFAULT;
			}
			else
			{
				std::cout << m_board[j][i].value;
			}
		}
		std::cout << "\n";
	}
}


Field* Map::getEnd()
{
	return m_end;
}


Field * Map::getStart()
{
	return m_start;
}



void Map::setStart(Field && start)
{
	m_board[start.y][start.x] = start;
	m_start = &m_board[start.y][start.x];
}




void Map::setEnd(Field  end)
{
	m_end = &m_board[end.y][end.x];
}


int Map::getHeight() const
{
	return m_heigth;
}


int Map::getWidth() const
{
	return m_width;
}
