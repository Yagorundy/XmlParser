#pragma once

#include <iostream>
#include "command_parser.h"
#include "../utils/app_exceptions.h"

namespace XmlParser {
	class App {
		AppState state_;

	public:
		void run();
	};
}