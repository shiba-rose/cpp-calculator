#include "variable.h"
#include "Token.h"
#include <iostream>
#include <stdexcept>

std::vector<Variable> names;

double get_value(std::string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	throw std::runtime_error("get: undefined name " + s);
}

void set_value(std::string s, double d)
{		
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	throw std::runtime_error("set: undefined name " + s);
}

bool is_declared(std::string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}