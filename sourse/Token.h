#pragma once
#ifndef TOKEN_H
#define TOKEN_H
#include <string>

//possible value type

static constexpr char let = 'L';
static constexpr char quit = 'Q';
static constexpr char print = ';';
static constexpr char number = '8';
static constexpr char name = 'a';

// struct for characters
struct Token {
	char kind;
	double value;
	std::string name;
	Token(char ch);
    Token(char ch, double val);
    Token(char ch, std::string n);
};

#endif