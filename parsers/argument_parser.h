#pragma once

#include "../utils/vector.hpp"
#include "../utils/MyString.h"

namespace XmlParser {
	class ArgumentParser {
	public:
		Vector<MyString> parse(const MyString& input);
	};
}