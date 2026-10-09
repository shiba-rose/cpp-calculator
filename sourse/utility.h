#ifndef UTILITY_H
#define UTILITY_H

void clean_up_mess();   
#include <string>
#include <sstream>
#include <stdexcept>


// error() simply disguises throws:
[[noreturn]] void error (const std::string& s);
[[noreturn]] void error (const std::string& s, const std::string& s2);
[[noreturn]] void error (const std::string& s, int i);
#endif