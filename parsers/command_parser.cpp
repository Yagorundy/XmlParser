#include "command_parser.h"

namespace XmlParser {
	Vector<MyString> CommandParser::parseArgs(const MyString& input) {
		Vector<MyString> args;
		int l = 0;
		int n = input.getSize();
		bool inQuotes = false;
		char quoteChar = '\0';

		while (l < n) {
			// skip leading whitespaces
			while (l < n && std::isspace(input[l])) {
				++l;
			}

			if (l >= n) {
				break;
			}

			size_t start = l;

			// argument starts with a quote
			if (input[l] == '"' || input[l] == '\'') {
				inQuotes = true;
				quoteChar = input[l];
				++l; // skip the opening quote
				start = l;
				while (l < n && (input[l] != quoteChar || (input[l] == quoteChar && input[l - 1] == '\\'))) {
					++l;
				}
				// include the content inside quotes
				if (l < n && input[l] == quoteChar) {
					args.pushBack(input.substr(start, l - start));
					++l; // skip the closing quote
				}
			}
			// argument does not start with a quote
			else {
				while (l < n && !std::isspace(input[l])) {
					++l;
				}
				args.pushBack(input.substr(start, l - start));
			}
		}

		//std::cout << "command parser: ";
		//for (int i = 0; i < args.getSize(); i++) {
		//    std::cout << args[i] << ' ';
		//}
		//std::cout << std::endl;

		return args;
	}

	Command* CommandParser::parseCommand(const MyString& input) {
		Vector<MyString> args = parseArgs(input);
		if (args.getSize() == 0) return nullptr;

		MyString name = args[0];
		args.popFront();

		auto command = Command::create(name, args);
		return command;
	}
}