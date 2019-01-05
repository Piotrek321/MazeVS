#pragma once
#include "Map.h"

class MapBuilder
{
public:
	MapBuilder();
	~MapBuilder();
	/*
	template<typename T>
	void generateMapBorders(T border, T emptyField)
	{
		/*
		for (int i = 0; i < m_heigth; ++i)
		{
			m_map[i][0] = border;
			m_map[i][m_width - 1] = border;
		}

		for (int i = 0; i < m_width; ++i)
		{
			m_map[0][i] = border;
			m_map[m_heigth - 1][i] = border;
		}

		for (int i = 1; i < m_heigth - 2; ++i)
		{
			for (int j = 1; j < m_width - 2; ++j)
			{
				m_map[i][j] = emptyField;
			}
		}
	}
	void generateStart()
	{
		/*
		// Seed with a real random value, if available
		std::random_device r;

		// Choose a random mean between 1 and 6
		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist_width(0, m_width - 1);
		m_start_x = uniform_dist_width(e1);
		if (m_start_x == 0 || m_start_x == m_width - 1)
		{
			std::uniform_int_distribution<int> uniform_dist_height(0, m_heigth - 1);

			m_start_y = uniform_dist_height(e1);
		}
		else
		{
			std::uniform_int_distribution<int> uniform_dist_height(0, 1);

			m_start_y = uniform_dist_height(e1);
		}

		//int meanHeight = uniform_dist_height(e1);


		std::cout << "m_start_x: " << m_start_x << '\n';
		std::cout << "m_start_y: " << m_start_y << '\n';

		m_end_x = uniform_dist_width(e1);
		std::uniform_int_distribution<int> uniform_dist_height(0, m_heigth - 1);

		m_end_y = uniform_dist_height(e1);

		std::cout << "m_end_x: " << m_end_x << '\n';
		std::cout << "m_end_x: " << m_end_y << '\n';
	}
	*/
	template<typename MapT, typename mapType>
	static void generateMap(MapT map)
	{ 
		static_assert(std::is_base_of<Map<mapType>, MapT>::value, "MapT must derive from Map");

		//generateStart();
	}
};
