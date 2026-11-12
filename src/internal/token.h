
#ifndef TOKEN_H
#define TOKEN_H
#include <string>


// Character codes identifying token kinds.
enum class Kind : char {
    none = 0,

    left_parenthesis = '(',
    right_parenthesis = ')',

    plus = '+',
    minus = '-',
    multiply = '*',
    divide = '/',
    modulo = '%',

    semicolon = ';',
    assign = '=',

    unconst = 'U',
    help = 'H',
    constant = 'C',
    let = 'L',
    quit = 'Q',

    calculate = 'A',
    global = 'g',
    local = 'l',


    number = '8',
    identifier = 'a',
    end_of_input = 'E',

    sine = 's',
    cosine = 'c',
    tangent = 't',
    degrees = 'd',
    radians = 'r'

};

// Represents a token read from the input.
struct Token {
	Kind kind;
	double value;
	std::string name;

	Token() : kind(Kind::none), value(0.0), name("") {};
	Token(char ch);
	Token(Kind ch);
    Token(double val);
    Token(std::string n);

	bool operator==(const Token& other) const;
	bool operator!=(const Token& other) const;
};

#endif