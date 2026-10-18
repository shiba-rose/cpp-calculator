#include "variable.h"
#include "grammar.h"


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
double Symbol_table::define_name(){

	Token t = ts.get();
	int flag_const = 0;
	if (t.kind == 'C' || t.kind == 'U')
	{
		if (t.kind == 'C') flag_const = 1;
		else flag_const = 2;
		t = ts.get();	
	}
	if (t.kind != 'a') error("name expected in declaration");
	std::string name = t.name;
	write_primer(name);
	Token t2 = ts.get();
	if (t2.kind != '=') 
	{
		if (flag_const == 1)
		{
			symbol_table.set_const(name);
		}

		else if (flag_const == 2)  
		{
			symbol_table.set_unconst(name);
		}

		return var_table[find_name_index(name)].value;
	}
	write_primer(t2.kind);
	double d = expression();
	if (symbol_table.is_declared(name))
	{
		symbol_table.set_value(name, d);
		if (flag_const == 1) symbol_table.set_const(name);
		if (flag_const == 2) symbol_table.set_unconst(name);
		return d;
	}
	
	symbol_table.push_back(name, d);
	if (flag_const == 1) symbol_table.set_const(name);
	return d;	
}