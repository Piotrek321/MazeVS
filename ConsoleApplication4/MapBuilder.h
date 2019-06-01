#pragma once
#include <boost/optional.hpp>
#include "Map.h"
#include <random>
#include "pch.h"
#include <cmath>
#include <stack>
#include "Globals.h"
class MapBuilder
{
public:
	enum Moves
	{
		Up,
		Down,
		Left,
		Right,
		Amount
	};
	std::vector<std::string> movesString{"Up", "Down", "Left", "Right"};
	std::string convertMoveToString(Moves move)
	{
		return movesString[move];
	}

	std::stack<Field*> m_FieldStack;
	Map & m_Map;
	std::vector<std::function<void(Field*&)>> m_Moves;
	Field * makeMove(Field *& field, Moves where)
	{
		field->value = emptyField;
		m_Moves[where](field);
		//field = &m_Map.m_board[field->y - step][field->x];
		field->value = playerSign;
		field->wasVisited = true;
		m_FieldStack.push(field);
		return field;
	}

	MapBuilder(Map &map) : m_Map(map)
	{
		m_Moves.reserve(Moves::Amount);

		//UP
		m_Moves.emplace_back([this](Field *& field)
		{
			field = &m_Map.m_board[field->y - step][field->x];
		});

		//DOWN
		m_Moves.emplace_back([this](Field *& field)
		{
			field = &m_Map.m_board[field->y + step][field->x];
		});

		//LEFT
		m_Moves.emplace_back([this](Field *& field)
		{
			field = &m_Map.m_board[field->y][field->x - step];
		});

		//RIGHT
		m_Moves.emplace_back([this](Field *& field)
		{
			field = &m_Map.m_board[field->y][field->x + step];
		});
	}

	std::vector<std::function<void(Map &, Field *)>>  m_MakeMove;
	~MapBuilder() {};


	void generateMap();


	void generateMapBorders() {}


	void generateStart();


	void generate_(Map& map);
	Moves chooseRandomDirection(std::vector<Moves> & availableMoves)
	{
		// Seed with a real random value, if available
		std::random_device r;

		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist_width(0, availableMoves.size() - 1);
		return availableMoves[uniform_dist_width(e1)];
	}
	/*
	boost::optional<Field*> chooseRandomDirection(std::vector<Field*> & availableMoves)
	{
		// Seed with a real random value, if available
		if (availableMoves.size() == 0)
			return boost::none;
		std::random_device r;

		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist_width(0, availableMoves.size() - 1);
		return availableMoves[uniform_dist_width(e1)];
	}*/



	//void  lookAround();//const Map& map, const FieldType& field);
	//One concern... maybe it would be better to have some other type of vector and then return vector which always has 4 elements
	// and then you can access it by vec[enum::UP] ?
	// i.e vector<optional<TYPE>> . Beause now it is harder to test. You have to remeber what the output of fc will be
	auto lookAround(  Field* field)
	{
		//std::vector<Field*> availableMoves;
		std::vector<Moves> availableMoves;
	
		auto lookUp = [&map = this->m_Map, &field, &availableMoves]()
		{
			if (!(field->y <= 0 || map.m_board[field->y - step][field->x].isBorder == true || map.m_board[field->y - step][field->x].wasVisited == true))
			{
				//std::cout << "Look up\n";
				availableMoves.push_back(Moves::Up);
				//availableMoves.push_back(&(map.m_board[field->y - step][field->x]));
			}

		};

		auto lookDown = [&map = this->m_Map, &field, &availableMoves]()
		{
			if (!(field->y + step >= map.getHeight() || map.m_board[field->y + step][field->x].isBorder == true || map.m_board[field->y + step][field->x].wasVisited == true))
			{
				//std::cout << "Look down\n";
				availableMoves.push_back(Moves::Down);

				//availableMoves.push_back(&(map.m_board[field->y + step][field->x]));
			}
		};

		auto lookLeft = [&map = this->m_Map, &field, &availableMoves]()
		{
			if (!(field->x - step < 0 || map.m_board[field->y][field->x - step].isBorder == true || map.m_board[field->y][field->x - step].wasVisited == true))
			{
				//std::cout << "Look left\n";
				availableMoves.push_back(Moves::Left);

				//availableMoves.push_back(&(map.m_board[field->y][field->x - step]));
			}
		};

		auto lookRight = [&map = this->m_Map, &field, &availableMoves]()
		{
			if (!(field->x + step >= map.getWidth() || map.m_board[field->y][field->x + step].isBorder == true || map.m_board[field->y][field->x + step].wasVisited == true))
			{
				//std::cout << "Look right\n";
				availableMoves.push_back(Moves::Right);

				//availableMoves.push_back(&(map.m_board[field->y][field->x + step]));
			}
		};

		lookUp();
		lookDown();
		lookLeft();
		lookRight();

		std::cout << "Available moves\n";

		for (const auto & move : availableMoves)
		{
			std::cout << convertMoveToString(move) << " ";
		}
		std::cout << "\n";
		return availableMoves;
	}


};
/*

std::vector lookAround(const Map& map, const FieldType& field)
{
	//auto lookUp = [&map,&field]()
	//{

		//map.m_board[field.y][field.x]
//	};
	//std::vector vec;
//	vec.push_back(map.m_board[0][0]);

}*/


void MapBuilder::generate_(Map& map)
{
	//LOOK AROUND
}



void MapBuilder::generateMap()
{
	generateStart();
	std::cout << m_Map << "\n";
	Field* currentField = m_Map.getStart();
	currentField->wasVisited = true;
	m_FieldStack.push(currentField);
	while (1)
	{
		auto availableFields = lookAround(currentField);

		if (availableFields.size() == 0)
		{
			return;
		}
		//availableFields.erase(std::remove(availableFields.begin(), availableFields.end(), m_FieldStack.top()), availableFields.end());
		auto chosenDirection = chooseRandomDirection(availableFields);
		std::cout << "Going " << convertMoveToString(chosenDirection) << "\n";
		std::cout << "Field before: " << *currentField << "\n";
		makeMove(currentField, chosenDirection);
		std::cout << "Field after: " << *currentField << "\n";

		/*
		currentField = chosenField;
			currentField->value = ' ';
			currentField->wasVisited = true;
			m_FieldStack.push(currentField);*/
		
		m_Map.printMap();
		int x = 10;
	}
}


void MapBuilder::generateStart()
{
	// Seed with a real random value, if available
	std::random_device r;

	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist_width(0,m_Map.getWidth() - 1);
	Field start{ uniform_dist_width(e1), 0, 'S' };
	
	if (start.x == 0 || start.x ==m_Map.getWidth() - 1)
	{
		std::uniform_int_distribution<int> uniform_dist_height(1,m_Map.getHeight() - 2);
		start.y = uniform_dist_height(e1);
	}
	else
	{
		std::uniform_int_distribution<int> uniform_dist_height(0, m_Map.getHeight() - 1);
		start.y = uniform_dist_height(e1);
	}

	std::cout << "m_start_x: " << start.x << '\n';
	std::cout << "m_start_y: " << start.y << '\n';

	m_Map.setStart(std::move(start));
}