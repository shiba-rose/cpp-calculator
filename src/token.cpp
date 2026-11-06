#include "token.h"
#include <string>

Token::Token(char ch) :kind(static_cast<TokenKind>(ch)), value(0) { }
Token::Token(double val) :kind(TokenKind::number), value(val) { }
Token::Token(std::string n) :kind(TokenKind::identifier), value(0), name(n) { }
Token::Token(TokenKind k) :kind(k), value(0) { }

bool Token::operator==(const Token& other) const {
    return kind == other.kind && value == other.value && name == other.name;
}

bool Token::operator!=(const Token& other) const {
    return !(*this == other);
}