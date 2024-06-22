#pragma once

#include <exception>

namespace XmlParser {
	class ValidationException : public std::exception {
		using std::exception::exception;
	};

	class InvalidArgumentsException : public ValidationException {
	public:
		InvalidArgumentsException();
	};
}