#include "calculator.h"
#include "token_stream.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "grammar.h"
#include "utility.h"
#include <stdexcept>



std::string calculator(std::string str)
{
    std::string str_result;
    std::istringstream stream(str);
    
    Token_stream token_stream;
    token_stream.set_input(stream);

    for (;;) {
        try {
            Token t = token_stream.get();

            while (t.kind == TokenKind::semicolon) 
                t = token_stream.get();

            if (t.kind == TokenKind::end_of_input)
                break;

            if (t.kind == TokenKind::quit)
                throw std::string("quit");

            if (t.kind == TokenKind::help) {
                str_result += help();
                continue;
            }

            token_stream.unget(t);
            std::ostringstream output;

            double value = statement(token_stream);
            std::ostringstream s;
            s << std::setprecision(15) << std::defaultfloat << value;
            std::string suffix = s.str() + " ";

            output << result << value;

            output << '\n';
            str_result = str_result + primer + output.str();
        }
        catch (const std::runtime_error& e) {
            str_result += std::string("Error: ") + e.what() + '\n';
            clean_up_mess(token_stream);
        }
    primer ="";
    }
    
    return str_result;
}