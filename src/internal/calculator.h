#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "utility.h"
#include <string>



std::string calculator(std::string str, Calculator_context& context);
const std::string prompt = "> ";
const std::string result = "= ";

#endif 