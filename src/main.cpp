#include <iostream>
#include <exception>
#include <sstream>
#include <string>
#include "calculator.h"
#include "utility.h"





void run_calculator()
{
	Calculator_context context;
	for(;;) 
	try {
		std::cout << ">";
		std::string input;

		if (!std::getline(std::cin, input)) return;
		std::string result {calculator(input,context)};
		std::cout << result;
	}

	catch (std::string s){
		return;
	}

	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		char c;
		while (std::cin >> c && c != ';');
	}
}

int main()
try {
	run_calculator();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
	return 1;
}
catch (...) {
	std::cerr << "exception\n";
	return 2;
}