#include "app/xml_parser.h"
#include <iostream>
#include <exception>


int main() {
	try {
		XmlParser::run();
	}
	catch (std::exception e) {
		std::cout << "An error occured: " << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cout << "An unexpected error occured!";
		return 1;
	}
}
