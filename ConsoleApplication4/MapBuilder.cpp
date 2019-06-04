#include "MapBuilder.h"
#include "Logger.h"

std::string MapBuilder::convertMoveToString(Moves move)
{
	return movesString[move];
}

Field * MapBuilder::makeMove(Field *& field, Moves where, bool addToStack)
{
	if (field != m_Map.getStart())
	{
		field->value = emptyField;
	}
	m_Moves[where](field);
	field->value = playerSign;
	field->wasVisited = true;
	if (addToStack)
	{
		m_FieldStack.push(field);
	}
	return field;
}

void MapBuilder::initializeDirections()
{
	m_Directions.reserve(Moves::Amount);

	m_Directions.emplace_back([&map = this->m_Map](Field * field)->boost::optional<Moves>
	{
		if (!(field->y <= 0 || map.m_board[field->y - step][field->x].isBorder == true || map.m_board[field->y - step][field->x].wasVisited == true))
		{
			return Moves::Up;
		}
		return boost::none;
	});

	m_Directions.emplace_back([&map = this->m_Map](Field * field)->boost::optional<Moves>
	{
		if (!(field->y + step >= map.getHeight() || map.m_board[field->y + step][field->x].isBorder == true || map.m_board[field->y + step][field->x].wasVisited == true))
		{
			return Moves::Down;
		}
		return boost::none;
	});

	m_Directions.emplace_back([&map = this->m_Map](Field * field)->boost::optional<Moves>
	{
		if (!(field->x - step < 0 || map.m_board[field->y][field->x - step].isBorder == true || map.m_board[field->y][field->x - step].wasVisited == true))
		{
			return Moves::Left;
		}
		return boost::none;
	});

	m_Directions.emplace_back([&map = this->m_Map](Field * field)->boost::optional<Moves>
	{
		if (!(field->x + step >= map.getWidth() || map.m_board[field->y][field->x + step].isBorder == true || map.m_board[field->y][field->x + step].wasVisited == true))
		{
			return Moves::Right;
		}
		return boost::none;
	});
}

void MapBuilder::initializeMoves()
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

MapBuilder::MapBuilder(Map &map) : m_Map(map)
{
	initializeMoves();
	initializeDirections();
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

	for (const auto & direction : m_Directions)
	{
		const auto & direction_ = direction(field);
		if (direction_)
		{
			availableMoves.emplace_back(direction_.get());
			logging::print(convertMoveToString(direction_.get()) + " ");
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
		logging::print("Going " + convertMoveToString(chosenDirection));
		logging::print("Field before: " + currentField->toString());
		makeMove(currentField, chosenDirection);
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
			logging::print("Putting wall " + convertMoveToString(availableFields[i]));

			makeMove(filedPtr, availableFields[i], false);
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