#include "calculator.h"
#include "Token.h"
#include "Token_stream.h"
#include <iostream>
#include "grammar.h"
#include "utility.h"
#include <stdexcept>



void calculate()
{
	while (true) try {
		std::cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		std::cout << result << statement() << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		clean_up_mess();
	}
}