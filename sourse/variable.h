#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include <utility>

#include "Token.h"
#include "Token_stream.h"	
#include "utility.h"		

//function for finding the value of a variable
struct Variable {
	bool const0;
	std::string name;
	double value;
	Variable(std::string n, double v) :const0(false), name(n), value(v) { }
	Variable(bool c, std::string n, double v) :const0(c), name(n), value(v) { }
};

extern std::vector<Variable> names;

double get_value(std::string s);
void set_value(std::string s, double d);
std::pair<bool, bool> is_declared(std::string s);

#endif