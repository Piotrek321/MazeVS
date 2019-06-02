#include "MapBuilder.h"

std::string MapBuilder::convertMoveToString(Moves move)
{
	return movesString[move];
}

Field * MapBuilder::makeMove(Field *& field, Moves where)
{
	if (field != m_Map.getStart())
	{
		field->value = emptyField;
	}
	m_Moves[where](field);
	field->value = playerSign;
	field->wasVisited = true;
	m_FieldStack.push(field);
	return field;
}

Field * MapBuilder::makeMove2(Field *& field, Moves where)
{
	if (field != m_Map.getStart())
	{
		field->value = emptyField;
	}
	m_Moves[where](field);
	field->value = playerSign;
	field->wasVisited = true;
	//m_FieldStack.push(field);
	return field;
}
void MapBuilder::temp(Field *& field, Moves where)
{

	m_Moves[where](field);
	field->value = playerSign;
	field->wasVisited = true;
	m_FieldStack.push(field);
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
		else
		{
			return boost::none;
		}
	});

	m_Directions.emplace_back([&map = this->m_Map](Field * field)->boost::optional<Moves>
	{
		if (!(field->y + step >= map.getHeight() || map.m_board[field->y + step][field->x].isBorder == true || map.m_board[field->y + step][field->x].wasVisited == true))
		{
			return Moves::Down;
		}
		else
		{
			return boost::none;
		}
	});

	m_Directions.emplace_back([&map = this->m_Map](Field * field)->boost::optional<Moves>
	{
		if (!(field->x - step < 0 || map.m_board[field->y][field->x - step].isBorder == true || map.m_board[field->y][field->x - step].wasVisited == true))
		{
			return Moves::Left;
		}
		else
		{
			return boost::none;
		}
	});

	m_Directions.emplace_back([&map = this->m_Map](Field * field)->boost::optional<Moves>
	{
		if (!(field->x + step >= map.getWidth() || map.m_board[field->y][field->x + step].isBorder == true || map.m_board[field->y][field->x + step].wasVisited == true))
		{
			return Moves::Right;
		}
		else
		{
			return boost::none;
		}
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
	// Seed with a real random value, if available
	std::random_device r;

	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist_width(0, availableMoves.size() - 1);
	return availableMoves[uniform_dist_width(e1)];
}

//void  lookAround();//const Map& map, const FieldType& field);
//One concern... maybe it would be better to have some other type of vector and then return vector which always has 4 elements
// and then you can access it by vec[enum::UP] ?
// i.e vector<optional<TYPE>> . Beause now it is harder to test. You have to remeber what the output of fc will be
auto MapBuilder::lookAround(Field* field)
{
	//std::vector<Field*> availableMoves;
	std::vector<Moves> availableMoves;
	std::cout << "Available moves:\n";

	for (const auto & direction : m_Directions)
	{
		const auto direction_ = direction(field);
		if (direction_)
		{
			availableMoves.emplace_back(direction_.get());
			std::cout << convertMoveToString(direction_.get()) << " ";
		}
	}

	std::cout << "\n";
	return availableMoves;
}

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

			while (availableFields.size() == 0)
			{
				std::cout << "No moves available. Current position is: " << *currentField << "\n";
				if (m_FieldStack.size() == 2)
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
					std::random_device r;
					std::default_random_engine e1(r());
					std::uniform_int_distribution<int> uniform_dist_width(0, fields.size() - 1);
					fields[uniform_dist_width(e1)]->value = endSign;
					currentField->value = emptyField;
					m_Map.printMap();

					return;
				}
				currentField->value = emptyField;
				m_FieldStack.pop();
				currentField = m_FieldStack.top();
				//m_FieldStack.pop();
				currentField->value = playerSign;
				std::cout << "After popping " << *currentField << "\n";
				availableFields = lookAround(currentField);
	
				m_Map.printMap();
			}
	
			//return;
		}
		//availableFields.erase(std::remove(availableFields.begin(), availableFields.end(), m_FieldStack.top()), availableFields.end());
		auto chosenDirection = chooseRandomDirection(availableFields);
		std::cout << "Going " << convertMoveToString(chosenDirection) << "\n";
		std::cout << "Field before: " << *currentField << "\n";
		makeMove(currentField, chosenDirection);
		std::cout << "Field after: " << *currentField << "\n";

		m_Map.printMap();
		availableFields = lookAround(currentField);

		if (availableFields.size() > 1)
		{

			std::cout << "availableFields.size(): " << availableFields.size() << "\n";
			
			//availableFields.erase(std::remove(availableFields.begin(), availableFields.end(), getOppositeMove(chosenDirection)), availableFields.end());
			std::random_device r;
			std::default_random_engine e1(r());
			std::uniform_int_distribution<int> uniform_dist_width(0, availableFields.size()-1);
			auto amount = uniform_dist_width(e1);
			std::cout << "Amount: " << amount << "\n";
			for (int i = 0; i < amount; ++i)
			{
				Field field = *currentField;
				Field * filedPtr = &field;
				std::cout << "Putting wall " << convertMoveToString(availableFields[i]) << "\n";

				makeMove2(filedPtr, availableFields[i]);
				filedPtr->value = borderSign;
				filedPtr->isBorder = true;
			}
		}

		m_Map.printMap();
		int x = 10;
	}
}


void MapBuilder::generateStart()
{
	// Seed with a real random value, if available
	std::random_device r;

	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist_width(0, m_Map.getWidth() - 1);
	Field start{ uniform_dist_width(e1), 0, startSign };

	if (start.x == 0 || start.x == m_Map.getWidth() - 1)
	{
		std::uniform_int_distribution<int> uniform_dist_height(1, m_Map.getHeight() - 2);
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