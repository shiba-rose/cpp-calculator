#ifndef GRAMMAR_H
#define GRAMMAR_H
#include "utility.h"
#include <cmath>

double expression(Calculator_context context);
double primary(Calculator_context context);
double term(Calculator_context context);
double declaration(Calculator_context context);
double statement(Calculator_context context);
void write_primer(std::string str);
void write_primer(double value);
void write_primer(TokenKind kind);


#endif
