#include "token_stream.h"
#include "variable.h"
#include "grammar.h"
#include "utility.h"
#include <iomanip>
#include <sstream>
// calculator grammar  
 
std::string primer;

void write_primer(std::string str)
{
	primer = primer + str + " ";
}

void write_primer(double value)
{
 	std::ostringstream stream;
    stream << std::setprecision(15) << std::defaultfloat << value;
    primer += stream.str() + " ";
}

void write_primer(char ch)
{
	std::string str {ch};
	primer = primer + str + " ";
}


double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	
		write_primer(t.kind);
		double d = expression();
	    t = ts.get();
		if (t.kind != ')') error("')' expected");
		write_primer(t.kind);
		return d;
	}
	case '-':
		write_primer(t.kind);
		return -primary();
	case number:
		write_primer(t.value);
		return t.value;
	case name:
		write_primer(t.name);
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
			write_primer(t.kind);
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		write_primer(t.kind);
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
			write_primer(t.kind);
			left += term();
			break;
		case '-':
			write_primer(t.kind);
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
