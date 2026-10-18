#include "calculator.h"
#include "token_stream.h"
#include <iostream>
#include <sstream>
#include "grammar.h"
#include "utility.h"
#include <stdexcept>



std::string calculator(std::string str)
{
    std::string str_result;
    std::istringstream stream(str);
    ts.set_input(stream);

    for (;;) {
        try {
            Token t = ts.get();

            while (t.kind == print)
                t = ts.get();

            if (t.kind == end_of_input)
                break;

            if (t.kind == quit)
                throw std::string("quit");

            ts.unget(t);
            std::ostringstream output;
            output << result << statement() << '\n';
            str_result += output.str();
        }
        catch (const std::runtime_error& e) {
            str_result += std::string("Error: ") + e.what() + '\n';
            clean_up_mess();
        }
    }
    return str_result;
}