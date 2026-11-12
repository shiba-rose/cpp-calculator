#include "token.h"


Token::Token(char ch) :kind(static_cast<Kind>(ch)), value(0), name("") { }
Token::Token(double val) :kind(Kind::number), value(val), name("") { }
Token::Token(std::string n) :kind(Kind::identifier), value(0), name(n) { }
Token::Token(Kind k) :kind(k), value(0), name("") { }

bool Token::operator==(const Token& other) const {
    return kind == other.kind && value == other.value && name == other.name;
}

bool Token::operator!=(const Token& other) const {
    return !(*this == other);
}