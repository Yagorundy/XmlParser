#include "command_parser.h"

namespace XmlParser {
	Command* CommandParser::parseCommand(const String& input) {
		Vector<String> args;
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

            if (input[l] == '"' || input[l] == '\'') {
                // argument starts with a quote
                inQuotes = true;
                quoteChar = input[l];
                ++l; // skip the opening quote
                start = l;
                while (l < n && (input[l] != quoteChar || (input[l] == quoteChar && input[l - 1] == '\\'))) {
                    ++l;
                }
                // include the content inside quotes
                if (l < n && input[l] == quoteChar) {
                    args.pushBack(input.substring(start, l - start));
                    ++l; // skip the closing quote
                }
            }
            else {
                // argument does not start with a quote
                while (l < n && !std::isspace(input[l])) {
                    ++l;
                }
                args.pushBack(input.substring(start, l - start));
            }
        }

        if (args.getSize() == 0) return nullptr;

        String name = args[0];
        args.popFront();

		//std::cout << name << ' ';
		//for (int i = 0; i < args.getSize(); i++) {
		//	std::cout << args[i] << ' ';
		//}
		//std::cout << std::endl;

		auto command = Command::create(name, args);
		return command;
	}
}