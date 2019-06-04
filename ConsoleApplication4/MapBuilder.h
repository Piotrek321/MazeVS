#pragma once
#include <boost/optional.hpp>
#include "Map.h"

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

	class MoveMaker
	{
	public:
		std::vector<std::string> movesString{ "Up", "Down", "Left", "Right" };

		std::string convertMoveToString(Moves move);
		std::vector<std::function<void(Field*&)>> m_Moves;
		std::vector<std::function<boost::optional<Moves>(Field*)>> m_Directions;
		Field *& makeMove(Field *& field, Moves where, Map & m_Map);
		void initializeMoves(Map & m_Map);
		void initializeDirections(Map & m_Map);
		bool isFieldValid(Field & field);

		
	};

	void decideAboutPuttingWalls(std::vector<Moves> & availableFields, Field * currentField);

	std::stack<Field*> m_FieldStack;
	Map & m_Map;

		void pickRandomStart(Field * currentField);


	MapBuilder(Map &map);

	std::vector<std::function<void(Map &, Field *)>>  m_MakeMove;
	~MapBuilder() = default;


	void generateMap();


	void generateMapBorders() {}


	void generateStart();

	Moves chooseRandomDirection(std::vector<Moves> & availableMoves);

	//void  lookAround();//const Map& map, const FieldType& field);
	//One concern... maybe it would be better to have some other type of vector and then return vector which always has 4 elements
	// and then you can access it by vec[enum::UP] ?
	// i.e vector<optional<TYPE>> . Beause now it is harder to test. You have to remeber what the output of fc will be
	auto lookAround(Field* field);

	MoveMaker moveMaker;
};