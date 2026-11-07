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


double primary(Token_stream& token_stream)
{
	Token t = token_stream.get();
	Token ind;
	double prov;
	switch (t.kind) {
	case TokenKind::left_parenthesis:
	{	
		write_primer(t.kind);
		double d = expression(token_stream);
	    t = token_stream.get();
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
        t = token_stream.get();
    }

    token_stream.unget(t);
    return sign * primary(token_stream);
}
	case TokenKind::number:
		ind = token_stream.get();
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
			token_stream.unget(ind);
		}
		write_primer(t.value);
		return t.value;
	case TokenKind::identifier:
		write_primer(t.name);
		return symbol_table.get_value(t.name);
	case TokenKind::sine:
		ind = token_stream.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after sin");
		token_stream.unget(ind);
		write_primer("sin");
		return std::sin(primary(token_stream));
	case TokenKind::cosine:
		ind = token_stream.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after cos");
		token_stream.unget(ind);
		write_primer("cos");
		return std::cos(primary(token_stream));
	case TokenKind::tangent:
		ind = token_stream.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after tg");
		token_stream.unget(ind);
		write_primer("tg");
		prov = primary(token_stream);
		if (std::abs(std::cos(prov)) < 1e-12)
    		error("tg is undefined for this value");
		return std::tan(prov);
	default:
		token_stream.unget(t);
		error("primary expected");
	}
}

double term(Token_stream& token_stream)
{
	double left = primary(token_stream);
	for(;;) {
		Token t = token_stream.get();
		switch (t.kind) {
		case TokenKind::multiply:
			write_primer(t.kind);
			left *= primary(token_stream);
			break;
		case TokenKind::divide:
		{
			write_primer(t.kind);	
			double d = primary(token_stream);
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		default:
			token_stream.unget(t);
			return	 left;
		}
	}
}

double expression(Token_stream& token_stream)
{
	double left = term(token_stream);
	for(;;) {
		Token t = token_stream.get();
		switch (t.kind) {
		case TokenKind::plus:
			write_primer(t.kind);
			left += term(token_stream);
			break;
		case TokenKind::minus:
			write_primer(t.kind);
			left -= term(token_stream);
			break;
		default:
			token_stream.unget(t);
			return left;
		}
	}
}

// function parses the declaration of a variable of the form "let name = expression"
double declaration(Token_stream& token_stream)
{
	return symbol_table.define_name(token_stream);

}

double statement(Token_stream& token_stream)
{
	Token t = token_stream.get();
	switch (t.kind) {
	case TokenKind::let:
		return declaration(token_stream);
	default:
		token_stream.unget(t);
		return expression(token_stream);
	}
}
