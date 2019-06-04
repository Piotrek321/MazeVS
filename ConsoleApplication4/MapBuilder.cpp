#include "MapBuilder.h"
#include "Logger.h"


MapBuilder::MapBuilder(Map &map) : m_Map(map)
{
	moveMaker.initializeMoves(map);
	moveMaker.initializeDirections(map);
}

MapBuilder::Moves MapBuilder::chooseRandomDirection(std::vector<Moves> & availableMoves)
{
	return availableMoves[getRandomValue(availableMoves.size() - 1)];
}

//void  lookAround();//const Map& map, const FieldType& field);
//One concern... maybe it would be better to have some other type of vector and then return vector which always has 4 elements
// and then you can access it by vec[enum::UP] ?
// i.e vector<optional<TYPE>> . Beause now it is harder to test. You have to remeber what the output of fc will be
auto MapBuilder::lookAround(Field* field)
{
	std::vector<Moves> availableMoves;
	logging::print("Available moves:");

	for (const auto & direction : moveMaker.m_Directions)
	{
		const auto & direction_ = direction(field);
		if (direction_)
		{
			availableMoves.emplace_back(direction_.get());
			logging::print(moveMaker.convertMoveToString(direction_.get()) + " ");
		}
	}
	logging::print("\n");

	return availableMoves;
}

void MapBuilder::pickRandomStart(Field * currentField)
{
	std::vector<Field*> fields;
	for (auto & column : m_Map.m_board)
	{
		for (auto & field : column)
		{
			if (emptyField == field.value)
			{
				fields.emplace_back(&field);
			}
		}
	}

	fields[getRandomValue(fields.size() - 1)]->value = endSign;
	currentField->value = emptyField;
	m_Map.printMap();
}

void MapBuilder::generateMap()
{
	generateStart();
	logging::print(m_Map);

	Field* currentField = m_Map.getStart();
	currentField->wasVisited = true;
	m_FieldStack.push(currentField);

	while (!m_FieldStack.empty())
	{
		auto availableFields = lookAround(currentField);

		while (availableFields.size() == 0)
		{
			logging::print("No moves available. Current position is: " + currentField->toString());
			if (m_FieldStack.size() == 2)
			{
				pickRandomStart(currentField);
				return;
			}
			currentField->value = emptyField;
			m_FieldStack.pop();
			currentField = m_FieldStack.top();
			currentField->value = playerSign;
			logging::print("After popping " + currentField->toString());
			availableFields = lookAround(currentField);

			m_Map.printMap();
		}

		auto chosenDirection = chooseRandomDirection(availableFields);
		logging::print("Going " + moveMaker.convertMoveToString(chosenDirection));
		logging::print("Field before: " + currentField->toString());
		m_FieldStack.push(moveMaker.makeMove(currentField, chosenDirection, m_Map));
		logging::print("Field after: " + currentField->toString());

		m_Map.printMap();
		availableFields = lookAround(currentField);

		decideAboutPuttingWalls(availableFields, currentField);

		m_Map.printMap();
	}
}

void MapBuilder::decideAboutPuttingWalls(std::vector<Moves> & availableFields, Field * currentField)
{
	if (availableFields.size() > 1)
	{
		logging::print("availableFields.size(): " + availableFields.size());

		auto amount = getRandomValue(availableFields.size() - 1);
		logging::print("Amount: " + amount);
		for (int i = 0; i < amount; ++i)
		{
			Field field = *currentField;
			Field * filedPtr = &field;
			logging::print("Putting wall " + moveMaker.convertMoveToString(availableFields[i]));

			moveMaker.makeMove(filedPtr, availableFields[i], m_Map);
			filedPtr->value = borderSign;
			filedPtr->isBorder = true;
		}
	}
}

void MapBuilder::generateStart()
{
	Field start{ getRandomValue(m_Map.getWidth() - 1), 0, startSign };

	if (start.x == 0 || start.x == m_Map.getWidth() - 1)
	{
		start.y = getRandomValue(m_Map.getHeight() - 2, 1);
	}
	else
	{
		start.y = getRandomValue(m_Map.getHeight() - 1);
	}

	logging::print("m_start_x: " + start.x);
	logging::print("m_start_y: " + start.y);

	m_Map.setStart(std::move(start));
}


std::string MapBuilder::MoveMaker::convertMoveToString(Moves move)
{
	return movesString[move];
}

Field *& MapBuilder::MoveMaker::makeMove(Field *& field, Moves where, Map & m_Map)
{
	if (field != m_Map.getStart())
	{
		field->value = emptyField;
	}
	m_Moves[where](field);
	field->value = playerSign;
	field->wasVisited = true;

	return field;
}

void MapBuilder::MoveMaker::initializeMoves(Map & m_Map)
{
	m_Moves.reserve(Moves::Amount);

	//UP
	m_Moves.emplace_back([&m_Map](Field *& field)
	{
		field = &m_Map.m_board[field->y - step][field->x];
	});

	//DOWN
	m_Moves.emplace_back([&m_Map](Field *& field)
	{
		field = &m_Map.m_board[field->y + step][field->x];
	});

	//LEFT
	m_Moves.emplace_back([&m_Map](Field *& field)
	{
		field = &m_Map.m_board[field->y][field->x - step];
	});

	//RIGHT
	m_Moves.emplace_back([&m_Map](Field *& field)
	{
		field = &m_Map.m_board[field->y][field->x + step];
	});
}
	void MapBuilder::MoveMaker::initializeDirections(Map &m_Map)
	{
		m_Directions.reserve(Moves::Amount);

		m_Directions.emplace_back([&m_Map, this](Field * field)->boost::optional<Moves>
		{
			if (field->y - step >= 0)
			{
				Field & nextField = m_Map.m_board[field->y - step][field->x];
				if (isFieldValid(nextField))
				{
					return Moves::Up;
				}
			}
			return boost::none;
		});

		m_Directions.emplace_back([&m_Map, this](Field * field)->boost::optional<Moves>
		{
			
			if (field->y + step < m_Map.getHeight())
			{
				Field & nextField = m_Map.m_board[field->y + step][field->x];
				if (isFieldValid(nextField))
				{
					return Moves::Down;
				}
			}
			return boost::none;
		});

		m_Directions.emplace_back([&m_Map, this](Field * field)->boost::optional<Moves>
		{
			if (field->x - step >= 0)
			{
				Field & nextField = m_Map.m_board[field->y][field->x - step];

				if (isFieldValid(nextField))
				{
					return Moves::Left;
				}
			}
			return boost::none;
		});

		m_Directions.emplace_back([&m_Map, this](Field * field)->boost::optional<Moves>
		{
			if (field->x + step < m_Map.getWidth())
			{
				Field & nextField = m_Map.m_board[field->y][field->x + step];
				if (isFieldValid(nextField))
				{
					return Moves::Right;
				}
			}
			return boost::none;
		});
	}

	bool MapBuilder::MoveMaker::isFieldValid(Field & field)
	{
		return !(field.isBorder == true || field.wasVisited == true);
	}

