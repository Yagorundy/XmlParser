#include "text_node.h"

namespace XmlParser {
	
	TextNode::TextNode()
	{ }

	TextNode::TextNode(const MyString& text)
		: text_(text)
	{ }

	Node* TextNode::clone() const {
		return new TextNode(*this);
	}

	const MyString& TextNode::getText() const {
		return text_;
	}

	void TextNode::pipe(std::ostream& out, int ident) const {
		pipeIdent(out, ident);
		out << text_;
	}
}