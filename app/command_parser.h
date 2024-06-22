#pragma once

#include "../commands/command.h"

namespace XmlParser {
	class CommandParser {
	public:
		Command* parseCommand(const String& input);
	};
}