#include "app.h"

namespace XmlParser {

	void App::run() {
		CommandParser command_parser;
		while (true) {
			try {
				MyString input;
				input.getLine(std::cin);

				Command* command = command_parser.parseCommand(input);
				if (command != nullptr) {
					command->exec(state_);
					delete command;
				}
			}
			catch (ValidationException ex) {
				std::cout << ex.what() << '\n';
			}
		}
	}
}