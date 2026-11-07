#include "token_stream.h"
#include "variable.h"
#include "grammar.h"
#include "utility.h"
#include <iomanip>
#include <sstream>
// calculator grammar  
 




double primary(Calculator_context context)
{
	Token t = context.token_stream.get();
	Token ind;
	double prov;
	switch (t.kind) {
	case TokenKind::left_parenthesis:
	{	
		write_input_text(context,t.kind);
		double d = expression(context);
	    t = context.token_stream.get();
		if (t.kind != TokenKind::right_parenthesis) error("')' expected");
		write_input_text(context,t.kind);
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
		write_input_text(context,t.kind);
        t = context.token_stream.get();
    }

    context.token_stream.unget(t);
    return sign * primary(context);
}
	case TokenKind::number:
		ind = context.token_stream.get();
		if (ind.kind == TokenKind::degrees) {
			write_input_text(context,t.value);
			write_input_text(context,"deg");
			const double pi = std::acos(-1.0);
			return t.value * pi / 180.0;
		}
		else if (ind.kind == TokenKind::radians) {
			write_input_text(context,t.value);
			write_input_text(context,"rad");
			return t.value;
		}
		else {
			context.token_stream.unget(ind);
		}
		write_input_text(context,t.value);
		return t.value;
	case TokenKind::identifier:
		write_input_text(context,t.name);
		return symbol_table.get_value(t.name);
	case TokenKind::sine:
		ind = context.token_stream.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after sin");
		context.token_stream.unget(ind);
		write_input_text(context,"sin");
		return std::sin(primary(context));
	case TokenKind::cosine:
		ind = context.token_stream.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after cos");
		context.token_stream.unget(ind);
		write_input_text(context,"cos");
		return std::cos(primary(context));
	case TokenKind::tangent:
		ind = context.token_stream.get();
		if (ind.kind != TokenKind::left_parenthesis) error("'(' expected after tg");
		context.token_stream.unget(ind);
		write_input_text(context,"tg");
		prov = primary(context);
		if (std::abs(std::cos(prov)) < 1e-12)
    		error("tg is undefined for this value");
		return std::tan(prov);
	default:
		context.token_stream.unget(t);
		error("primary expected");
	}
}

double term(Calculator_context context)
{
	double left = primary(context);
	for(;;) {
		Token t = context.token_stream.get();
		switch (t.kind) {
		case TokenKind::multiply:
			write_input_text(context,t.kind);
			left *= primary(context);
			break;
		case TokenKind::divide:
		{
			write_input_text(context,t.kind);	
			double d = primary(context);
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		default:
			context.token_stream.unget(t);
			return	 left;
		}
	}
}

double expression(Calculator_context context)
{
	double left = term(context);
	for(;;) {
		Token t = context.token_stream.get();
		switch (t.kind) {
		case TokenKind::plus:
			write_input_text(context,t.kind);
			left += term(context);
			break;
		case TokenKind::minus:
			write_input_text(context,t.kind);
			left -= term(context);
			break;
		default:
			context.token_stream.unget(t);
			return left;
		}
	}
}

// function parses the declaration of a variable of the form "let name = expression"
double declaration(Calculator_context context)
{
	return symbol_table.define_name(context);

}

double statement(Calculator_context context)
{
	Token t = context.token_stream.get();
	switch (t.kind) {
	case TokenKind::let:
		return declaration(context);
	default:
		context.token_stream.unget(t);
		return expression(context);
	}
}
