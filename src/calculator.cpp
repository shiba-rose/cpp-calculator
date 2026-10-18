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

            double value = statement();
            std::ostringstream s;
            s << std::setprecision(15) << std::defaultfloat << value;
            std::string suffix = s.str() + " ";

            if (primer.size() < suffix.size() ||
                primer.compare(primer.size() - suffix.size(), suffix.size(), suffix) != 0)
                output << result << value;

            output << '\n';
            str_result = str_result + primer + output.str();
        }
        catch (const std::runtime_error& e) {
            str_result += std::string("Error: ") + e.what() + '\n';
            clean_up_mess();
        }
    primer ="";
    }
    
    return str_result;
}