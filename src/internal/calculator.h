#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "utility.h"
#include <string>


std::string calculate_file( const std::string& file_path, Calculator_context& context);
std::string calculator(std::string str, Calculator_context& context);
const std::string prompt = "> ";
const std::string result = "= ";

#endif 