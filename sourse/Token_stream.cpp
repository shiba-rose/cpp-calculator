#include "Token_stream.h"
#include <iostream>
#include "utility.h"

Token_stream ts;

// Reads input and converts it into tokens

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	std::cin >> ch;
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
		return Token(ch);
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
	{	std::cin.unget();
	double val;

	if (!(std::cin >> val)){
		std::cin.clear(); // return the last character read to the input stream
		clean_up_mess();
    	error("Invalid number");
	}
	return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch == '_') {
			std::string s;
			s += ch;
			while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			std::cin.unget();
			if (s == "let") return Token(let);
			if (s == "quit") return Token(quit);
			return Token(name, s);
		}
		error("Bad token");
	}
}


void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (std::cin >> ch)
		if (ch == c) return;
}