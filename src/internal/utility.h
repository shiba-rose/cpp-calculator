#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iomanip>

#include "token.h"
#include "token_stream.h"
#include "variable.h"

struct Calculator_context {
    Token_stream token_stream;
    Symbol_table symbol_table;
    std::string text_input;
};


void clean_up_mess(Calculator_context& context); 

// error() simply disguises throws:
[[noreturn]] void error (const std::string& s);
[[noreturn]] void error (const std::string& s, const std::string& s2);
[[noreturn]] void error (const std::string& s, int i);

void write_input_text(Calculator_context& context, std::string str);
void write_input_text(Calculator_context& context, double value);
void write_input_text(Calculator_context& context, TokenKind kind);

std::string help();
#endif