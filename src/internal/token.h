
#ifndef TOKEN_H
#define TOKEN_H
#include <string>

// Character codes identifying token kinds.
static constexpr char unconst0 = 'U';
static constexpr char help1 = 'H';
static constexpr char const0 = 'C';
static constexpr char let = 'L';
static constexpr char quit = 'Q';
static constexpr char print = ';';
static constexpr char number = '8';
static constexpr char name = 'a';
static constexpr char end_of_input = 'E';
static constexpr char sin0 = 's';
static constexpr char cos0 = 'c';
static constexpr char tg0 = 't';
static constexpr char deg0 = 'd';
static constexpr char rad0 = 'r';

// Represents a token read from the input.
struct Token {
	char kind;
	double value;
	std::string name;
	Token() : kind(0), value(0.0), name("") {};
	Token(char ch);
    Token(char ch, double val);
    Token(char ch, std::string n);
};

#endif