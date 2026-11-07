#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include "token.h"
#include <istream>
#include <unordered_map>

const std::string symbols = "()+-*/%;=";
const std::string numbers = ".0123456789";

const std::unordered_map<std::string, TokenKind> keywords = {
    {"let", TokenKind::let},
    {"quit", TokenKind::quit},
    {"const", TokenKind::constant},
    {"unconst", TokenKind::unconst},
    {"help", TokenKind::help},
    {"sin", TokenKind::sine},
    {"cos", TokenKind::cosine},
    {"tg", TokenKind::tangent},
    {"deg", TokenKind::degrees},
    {"rad", TokenKind::radians},
    {"calculate", TokenKind::calculate}
};

// Reads tokens from the input and supports one-token buffering.

class Token_stream {
    std::istream* stream;
    bool full;
    Token buffer;

public:
    Token_stream() : stream(nullptr), full(false), buffer() { }
    Token get();

    void set_input(std::istream& s) {
        stream = &s;
        full = false;
    }
    
    void unget(Token t) { buffer = t; full = true; }
    void ignore(TokenKind c);
};


#endif