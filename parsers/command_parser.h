#pragma once

#include "../commands/command.h"

// TODO: maybe rename to arguments parser and move Command creation elsewhere
namespace XmlParser {
	class CommandParser {
	public:
		Vector<MyString> parseArgs(const MyString& input);
		Command* parseCommand(const MyString& input);
	};
}