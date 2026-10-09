#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include <vector>
#include "Token.h"
#include "Token_stream.h"


struct Variable {
	std::string name;
	double value;
	Variable(std::string n, double v) :name(n), value(v) { }
};

extern std::vector<Variable> names;

double get_value(std::string s);
void set_value(std::string s, double d);
bool is_declared(std::string s);

#endif