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

void write_primer(TokenKind kind)
{
	std::string str {static_cast<char>(kind)};
	primer = primer + str + " ";
}


double primary()
{
	Token t = ts.get();
	Token ind;
	double prov;
	switch (t.kind) {
	case TokenKind::left_parenthesis:
	{	
		write_primer(t.kind);
		double d = expression();
	    t = ts.get();
		if (t.kind != TokenKind::right_parenthesis) error("')' expected");
		write_primer(t.kind);
		return d;
	}
	case TokenKind::plus:
	case TokenKind::minus:
	{
    int sign = 1;

    for(;;) {
        if (t.kind == TokenKind::minus) {
            sign = -sign;
        }

        else if (t.kind != TokenKind::plus) {
            break;
        }
		write_primer(t.kind);
        t = ts.get();
    }

    ts.unget(t);
    return sign * primary();
}
	case TokenKind::number:
		ind = ts.get();
		if (ind.kind == TokenKind::degrees) {
			write_primer(t.value);
			write_primer("deg");
			const double pi = std::acos(-1.0);
			return t.value * pi / 180.0;
		}
		else if (ind.kind == TokenKind::radians) {
			write_primer(t.value);
			write_primer("rad");
			return t.value;
		}
		else {
			ts.unget(ind);
		}
		write_primer(t.value);
		return t.value;
	case TokenKind::identifier:
		write_primer(t.name);
		return symbol_table.get_value(t.name);
	case TokenKind::sine:
		ind = ts.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after sin");
		ts.unget(ind);
		write_primer("sin");
		return std::sin(primary());
	case TokenKind::cosine:
		ind = ts.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after cos");
		ts.unget(ind);
		write_primer("cos");
		return std::cos(primary());
	case TokenKind::tangent:
		ind = ts.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after tg");
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
		case TokenKind::multiply:
			write_primer(t.kind);
			left *= primary();
			break;
		case TokenKind::divide:
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
		case TokenKind::plus:
			write_primer(t.kind);
			left += term();
			break;
		case TokenKind::minus:
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
	case TokenKind::let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}
