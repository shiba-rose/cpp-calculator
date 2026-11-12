#include "token_stream.h"
#include <iostream>
#include "utility.h"
#include <cctype>



// Reads input and converts it into tokens

Token Token_stream::get()
{
	char ch;

	if (full) { full = false; return buffer; }
	
	if (!(*stream >> ch)) return Token(Kind::end_of_input);
	
	auto it = operations.find(ch);
	if (it != operations.end()) return Token(it->second);

	if (numbers.find(ch) != std::string::npos)
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
	
	
	if (isalpha(ch)) {
		std::string s;
		s += ch;

		while (stream->get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
		stream->unget(); // return the last character read to the input stream

		auto it = keywords.find(s);
		if (it != keywords.end()) return Token(it->second);
		
		return Token(s);
	}
 
	error("Bad token");	
}


void Token_stream::ignore(Kind c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (*stream >> ch)
	{
		auto it = operations.find(ch);
		if (it == operations.end()) continue;
		
		if (Token(it->second) == c) return; 
	}
}

std::string Token_stream::get_file_path()
{
    std::string file_path;
    char ch;

    while (stream->get(ch) && std::isspace(static_cast<unsigned char>(ch))){}

    if (!*stream || ch != '"')
        error("file path expected");

    while (stream->get(ch) && ch != '"')
        file_path += ch;

    if (!*stream)
    	error("Closing quotation mark expected");

    if (file_path.empty())
        error("File path cannot be empty");

    return file_path;
}