#include "token_stream.h"
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
		return symbol_table.get_value(t.name);
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
	return symbol_table.define_name();

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
