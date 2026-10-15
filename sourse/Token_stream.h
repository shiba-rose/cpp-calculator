#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "Token.h"

// Reads tokens from the input and supports one-token buffering.

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(false), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

extern Token_stream ts;

#endif