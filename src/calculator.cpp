#include "calculator.h"
#include "token_stream.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "grammar.h"
#include "utility.h"
#include <stdexcept>
#include <fstream>
#include <filesystem>


std::string calculator(std::string str, Calculator_context& context)
{
    std::string str_result;
    std::istringstream stream(str);
    
    std::string input_text;
    context.token_stream.set_input(stream);

    for (;;) {
        try {
            Token t = context.token_stream.get();

            while (t.kind == TokenKind::semicolon) 
                t = context.token_stream.get();

            if (t.kind == TokenKind::end_of_input)
                break;

            if (t.kind == TokenKind::quit)
                throw std::string("quit");

            if (t.kind == TokenKind::help) {
                str_result += help();
                continue;
            }

            if (t.kind == TokenKind::calculate) 
            {
                std::string file_path = context.token_stream.get_file_path();

                str_result += calculate_file(file_path, context);

                context.token_stream.set_input(stream);

                continue;
            }

            context.token_stream.unget(t);
            std::ostringstream output;

            double value = statement(context);
            std::ostringstream s;
            s << std::setprecision(15) << std::defaultfloat << value;
            std::string suffix = s.str() + " ";

            output << result << value;

            output << '\n';
            str_result = str_result + context.text_input + output.str();
        }
        catch (const std::runtime_error& e) {
            str_result += std::string("Error: ") + e.what() + '\n';
            clean_up_mess(context);
        }
    context.text_input = "";
    }
    
    return str_result;
}

std::string calculate_file(
    const std::string& file_path,
    Calculator_context& context)
{
    std::filesystem::path path = std::filesystem::weakly_canonical(file_path);

    std::stack<std::string> temp = context.file_stack;
    while (!temp.empty()) {
    if (temp.top() == path.string())
        throw std::runtime_error("Recursive file calculation: " + path.string());

    temp.pop();
    }

    context.file_stack.push(path.string());

    std::ifstream file(file_path);
    
    if (!file) throw std::runtime_error("Cannot open file: " + file_path);

    try {
        std::string line;
        std::string output;

        while (std::getline(file, line))  output += calculator(line, context);

        context.file_stack.pop();
        return output;
    }
    catch (...) {
    context.file_stack.pop();
    throw;
    }
}