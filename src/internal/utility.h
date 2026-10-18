#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <string>

#include "token.h"
#include "token_stream.h"


void clean_up_mess(); 

// error() simply disguises throws:
[[noreturn]] void error (const std::string& s);
[[noreturn]] void error (const std::string& s, const std::string& s2);
[[noreturn]] void error (const std::string& s, int i);
#endif