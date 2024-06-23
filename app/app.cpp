#include "app.h"

namespace XmlParser {

	void App::run() {
		ArgumentParser argsParser;
		while (true) {
			try {
				MyString input;
				input.getLine(std::cin);

				Vector<MyString> args = argsParser.parse(input);
				if (args.getSize() == 0) continue;

				MyString name = args[0];
				if (name == "exit")
					break;

				args.popFront();
				Command* command = Command::create(name, args);
				command->exec(state_);
				delete command;
			}
			catch (ValidationException ex) {
				std::cout << ex.what() << '\n';
			}
		}
	}
}