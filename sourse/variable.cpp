#include "variable.h"

std::vector<Variable> names;

// function for finding the value of a variable

double get_value(std::string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

//variable value replacement function

void set_value(std::string s, double d, bool const0)
{	
	if (const0) error(s, " is a constant");	
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

// variable existence check function

std::pair<bool, bool> is_declared(std::string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) 
		{
			if (names[i].const0 == true) return {true, true};
			return {true, false};	
		}
	return {false, false};
}
