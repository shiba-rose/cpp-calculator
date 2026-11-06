#include "token_stream.h"
#include <iostream>
#include "utility.h"
#include <cctype>

Token_stream ts;

// Reads input and converts it into tokens

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	if (!(*stream >> ch)) {
    	return Token(TokenKind::end_of_input);
	}
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	{
		return Token(ch);
	}
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	
		stream->unget(); // return the last character read to the input stream
		double val;

		if (!(*stream >> val))
		{
			stream->clear(); 
    		error("Invalid number");
		}

	return Token(val);
	}
	default:
		if (isalpha(ch)) {
			std::string s;
			s += ch;
			while (stream->get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			stream->unget(); // return the last character read to the input stream
			if (s == "let") return Token(TokenKind::let);
			if (s == "quit") return Token(TokenKind::quit);
			if (s == "const") return Token(TokenKind::constant);
			if (s == "unconst") return Token(TokenKind::unconst);
			if (s == "help") return Token(TokenKind::help);
			if (s == "sin") return Token(TokenKind::sine);
			if (s == "cos") return Token(TokenKind::cosine);
			if (s == "tg") return Token(TokenKind::tangent);
			if (s == "deg") return Token(TokenKind::degrees);
			if (s == "rad") return Token(TokenKind::radians);
			return Token(s);
		}
		error("Bad token");	
	}
}


void Token_stream::ignore(TokenKind c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (*stream >> ch)
		if (ch == static_cast<char>(c)) return;
}