#include "token_stream.h"
#include <iostream>
#include "utility.h"

Token_stream ts;

// Reads input and converts it into tokens

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	if (!(*stream >> ch)) {
    	return Token(end_of_input);
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
	{	stream->unget();; // return the last character read to the input stream
	double val;

	if (!(*stream >> val)){
		std::cin.clear(); 
		clean_up_mess();
    	error("Invalid number");
	}
	return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			std::string s;
			s += ch;
			while (stream->get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			stream->unget(); // return the last character read to the input stream
			if (s == "let") return Token(let);
			if (s == "quit") return Token(quit);
			if (s == "const") return Token(const0);
			if (s == "unconst") return Token(unconst0);
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
	while (*stream >> ch)
		if (ch == c) return;
}