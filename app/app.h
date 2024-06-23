#pragma once

#include <iostream>
#include "../parsers/argument_parser.h"
#include "../utils/app_exceptions.h"
#include "app_state.h"
#include "../commands/command.h"

namespace XmlParser {
	class App {
		AppState state_;

	public:
		void run();
	};
}