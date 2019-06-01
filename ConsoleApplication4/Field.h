#pragma once
#include <iostream>
struct Field
{
	Field(int x, int y, char value) : x(x), y(y), value(value) {}
	Field(int x, int y) : x(x), y(y) {}
	Field() { std::cout << "FIELD()\n\n\n"; }
	Field(char value) :value(value) {}

	bool operator==(const Field & other) const
	{
		if(x == other.x && y == other.y && value == other.value && isBorder == other.isBorder)
		{
			return true;
		}
		return false;
	}

	int x = 0;
	int y = 0;
	char value;
	bool isBorder = false;
	bool wasVisited = false;
	friend std::ostream &operator << (std::ostream & os, const Field& field)
	{

		os << "\nX : " << field.x << " y: " << field.y << "\nvalue: " << field.value << "\nisBorder: " << field.isBorder << "\nwasVisited: " << field.wasVisited << "\n";

		return os;
	}
};
