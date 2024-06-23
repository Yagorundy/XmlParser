#pragma once

#include <iostream>

namespace XmlParser {
	class Node {
	protected:
		void pipeIdent(std::ostream& out, int ident) const;

	public:
		Node();
		virtual Node* clone() const = 0;
		virtual void pipe(std::ostream& out, int ident) const = 0;
	};
}
