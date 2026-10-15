#include "variable.h"

std::vector<Variable> names;


size_t find_name_index(std::string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) 
			return i;	
	error("find: undefined name ", s);
	return 0;
}

// function for finding the value of a variable

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
			if (names[i].const0) error(s, " is a constant");
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

// variable existence check function

bool is_declared(std::string s)
{
	for (size_t i = 0; i < names.size(); ++i)
		if (names[i].name == s) 
			return true;	
	return false;
}

void set_const(std::string name)
{
	size_t index = find_name_index(name);
	names[index].const0 = true;
}


void set_unconst(std::string name)
{
	size_t index = find_name_index(name);
	names[index].const0 = false;
}