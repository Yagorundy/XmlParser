#include "text_node.h"

namespace XmlParser {
	
	TextNode::TextNode()
	{ }

	Node* TextNode::clone() const {
		return new TextNode(*this);
	}

	const String& TextNode::getText() const {
		return text_;
	}

	void TextNode::pipe(std::ostream& out) const {
		out << text_;
	}
}