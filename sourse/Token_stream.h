#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "Token.h"

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