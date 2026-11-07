#ifndef GRAMMAR_H
#define GRAMMAR_H
#include <cmath>

double expression(Token_stream& token_stream);
double primary(Token_stream& token_stream);
double term(Token_stream& token_stream);
double declaration(Token_stream& token_stream);
double statement(Token_stream& token_stream);
void write_primer(std::string str);
void write_primer(double value);
void write_primer(TokenKind kind);

extern std::string primer;
#endif
