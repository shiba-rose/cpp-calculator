#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "token.h"
#include <istream>

// Reads tokens from the input and supports one-token buffering.

class Token_stream {
    std::istream* stream;
    bool full;
    Token buffer;

public:
    Token_stream() : stream(nullptr), full(false), buffer(0) { }

    void set_input(std::istream& s) {
        stream = &s;
        full = false;
    }

    Token get();
    void unget(Token t) { buffer = t; full = true; }

    void ignore(char);
};

extern Token_stream ts;
#endif