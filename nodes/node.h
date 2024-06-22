#pragma once

#include <iostream>
#include "../utils/string.h"

namespace XmlParser {
	class Node {
	public:
		Node();
		virtual Node* clone() const = 0;
		virtual void pipe(std::ostream& out) const = 0;
	};
}
