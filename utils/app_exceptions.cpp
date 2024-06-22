#include "app_exceptions.h"

namespace XmlParser {

	InvalidArgumentsException::InvalidArgumentsException()
		: ValidationException("Invalid arguments!")
	{ };
}