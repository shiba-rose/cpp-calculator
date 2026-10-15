#include "variable.h"
#include "Token.h"	
#include "utility.h"

std::vector<Variable> names;

//function for finding the value of a variable

double get_value(std::string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

//variable value replacement function

void set_value(std::string s, double d)
{		
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

// variable existence check function

bool is_declared(std::string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}