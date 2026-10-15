#pragma once
#ifndef TOKEN_H
#define TOKEN_H
#include <string>

// Character codes identifying token kinds.
static constexpr char unconst0 = 'U';
static constexpr char const0 = 'C';
static constexpr char let = 'L';
static constexpr char quit = 'Q';
static constexpr char print = ';';
static constexpr char number = '8';
static constexpr char name = 'a';

// Represents a token read from the input.
struct Token {
	char kind;
	double value;
	std::string name;
	Token(char ch);
    Token(char ch, double val);
    Token(char ch, std::string n);
};

#endif