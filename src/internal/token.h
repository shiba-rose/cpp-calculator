
#ifndef TOKEN_H
#define TOKEN_H
#include <string>


// Character codes identifying token kinds.
enum class Kind {
    none,

    left_parenthesis,
    right_parenthesis,

    plus,
    minus,
    multiply,
    divide,
    remainder,

    semicolon,
    assign,

    unconst,
    help,
    constant,
    let,
    quit,

    calculate,
    global,
    local,


    number,
    identifier,
    end_of_input ,

    sine ,
    cosine,
    tangent,
    degrees,
    radians 

};

// Represents a token read from the input.
struct Token {
	Kind kind;
	double value;
	std::string name;

	Token() : kind(Kind::none), value(0.0), name("") {};
	Token(Kind ch);
    Token(double val);
    Token(std::string n);

	bool operator==(const Token& other) const;
	bool operator!=(const Token& other) const;
};

#endif