#include "Token_stream.h"
#include "variable.h"
#include "grammar.h"
#include "utility.h"
// calculator grammar  
 
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	
		double d = expression();
	    t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	for(;;) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		default:
			ts.unget(t);
			return	 left;
		}
	}
}

double expression()
{
	double left = term();
	for(;;) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

// function parses the declaration of a variable of the form "let name = expression"
double declaration()
{
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
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	if (is_declared(name))
	{
		if (flag_const == 2) set_unconst(name);
		set_value(name, d);
		return d;
	}
	
	if (flag_const == 1) set_const(name);
	names.push_back(Variable(name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}
