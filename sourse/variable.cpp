#include "variable.h"



Symbol_table symbol_table;

size_t Symbol_table::find_name_index(std::string s)
{
	for (size_t i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) 
			return i;	
	error("find: undefined name ", s);
	return 0;
}

// function for finding the value of a variable

double Symbol_table::get_value(std::string s)
{
	for (size_t i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ",s);
}

//variable value replacement function

void Symbol_table::set_value(std::string s, double d)
{		
	for (size_t i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) {
			if (var_table[i].const0) error(s, " is a constant");
			var_table[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

// variable existence check function

bool Symbol_table::is_declared(std::string s)
{
	for (size_t i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) 
			return true;	
	return false;
}

void Symbol_table::set_const(std::string name)
{
	size_t index = find_name_index(name);
	var_table[index].const0 = true;
}


void Symbol_table::set_unconst(std::string name)
{
	size_t index = find_name_index(name);
	var_table[index].const0 = false;
}


void Symbol_table::push_back(std::string s, double d){
	var_table.push_back(Variable(s, d));
}