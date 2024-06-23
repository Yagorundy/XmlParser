#include "number_helpers.h"

namespace XmlParser {
	int parseInt(const char* str) {
		size_t result = 0;
		for (size_t i = 0; str[i] != '\0'; i++) {
			char ch = str[i];
			if (ch < '0' || ch > '9')
				throw ValidationException("Invalid number!");
			result = result * 10;
			result += ch - '0';
		}
		return result;
	}
}