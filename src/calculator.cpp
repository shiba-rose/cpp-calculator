#include "calculator.h"
#include "token_stream.h"
#include <iostream>
#include "grammar.h"
#include "utility.h"
#include <stdexcept>



std::string calculate(std::string str)
{
	std::string result;
	for(;;) 
	try {
		std::cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) throw "quit";
		ts.unget(t);
		std::cout << result << statement() << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		clean_up_mess();
	}
	
	return result;
}