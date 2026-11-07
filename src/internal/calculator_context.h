#ifndef CALCULATOR_CONTEXT_H
#define CALCULATOR_CONTEXT_H

#include <string>
#include "token_stream.h"
#include "variable.h"
#include <stack>

struct Calculator_context {
    Token_stream token_stream;
    Symbol_table symbol_table;
    std::string text_input;
    std::stack<std::string> file_stack;
};

#endif