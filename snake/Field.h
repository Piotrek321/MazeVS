#pragma once

struct Field
{
	Field(int x, int y, char value) : x(x), y(y), value(value) {}
	Field() {}
	int x =0;
	int y =0;
	char value;

};