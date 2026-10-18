#ifndef GRAMMAR_H
#define GRAMMAR_H

double expression();
double primary();
double term();
double declaration();
double statement();
void write_primer(std::string str);
void write_primer(double value);
void write_primer(char ch);

extern std::string primer;
#endif
