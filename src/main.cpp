#include <iostream>
#include <exception>
#include <sstream>
#include <string>
#include "calculator.h"



void run_calculator()
{
	std::cout << ">";
	for(;;) 
	try {
	std::string input;
	std::getline(std::cin, input);
	std::string result {calculator(input)};
	std::cout << result << std::endl;
	}

	catch (std::string error_message){
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
	char c;
	while (std::cin >> c && c != ';');
	return 1;
}
catch (...) {
	std::cerr << "exception\n";
	char c;
	while (std::cin >> c && c != ';');
	return 2;
}