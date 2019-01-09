#pragma once

struct Field
{
	Field(int x, int y, char value) : x(x), y(y), value(value) {}
	Field(int x, int y) : x(x), y(y) {}
	Field() {}
	Field(char value) :value(value){}
	int x =0;
	int y =0;
	char value;
	bool isBorder = false;

};