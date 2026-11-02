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
	Token ind;
	double prov;
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
	case '+':
	case '-':
	{
    int sign = 1;

    for(;;) {
        if (t.kind == '-') {
            sign = -sign;
        }

        else if (t.kind != '+') {
            break;
        }
		write_primer(t.kind);
        t = ts.get();
    }

    ts.unget(t);
    return sign * primary();
}
	case number:
		ind = ts.get();
		if (ind.kind == deg0) {
			write_primer(t.value);
			write_primer("deg");
			const double pi = std::acos(-1.0);
			return t.value * pi / 180.0;
		}
		else if (ind.kind == rad0) {
			write_primer(t.value);
			write_primer("rad");
			return t.value;
		}
		else {
			ts.unget(ind);
		}
		write_primer(t.value);
		return t.value;
	case name:
		write_primer(t.name);
		return symbol_table.get_value(t.name);
	case sin0:
		ind = ts.get();
		if (ind.kind != '(') error("'(' expected after sin");
		ts.unget(ind);
		write_primer("sin");
		return std::sin(primary());
	case cos0:
		ind = ts.get();
		if (ind.kind != '(') error("'(' expected after cos");
		ts.unget(ind);
		write_primer("cos");
		return std::cos(primary());
	case tg0:
		ind = ts.get();
		if (ind.kind != '(') error("'(' expected after tg");
		ts.unget(ind);
		write_primer("tg");
		prov = primary();
		if (std::abs(std::cos(prov)) < 1e-12)
    		error("tg is undefined for this value");
		return std::tan(prov);
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
		{
			write_primer(t.kind);	
			double d = primary();
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
