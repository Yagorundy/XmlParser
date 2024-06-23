#include "node.h"

namespace XmlParser {
	Node::Node() { }

	void Node::pipeIdent(std::ostream& out, int ident) const {
		for (int i = 0; i < ident; i++) {
			out << '\t';
		}
	}
}