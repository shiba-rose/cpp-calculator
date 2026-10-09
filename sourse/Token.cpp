#include "Token.h"
#include "Token_stream.h"
#include <string>

Token::Token(char ch) :kind(ch), value(0) { }
Token::Token(char ch, double val) :kind(ch), value(val) { }
Token::Token(char ch, std::string n) :kind(ch), name(n) { }
