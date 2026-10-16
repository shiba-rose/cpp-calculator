#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>

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

class Symbol_table {
    std::vector<Variable> var_table;

public:
    size_t find_name_index(std::string s);
	double get_value(std::string s);
	void set_value(std::string s, double d);
	bool is_declared(std::string s);
	void set_const(std::string name);
	void set_unconst(std::string name);
	void push_back(std::string s, double d);
};

extern Symbol_table symbol_table;
#endif