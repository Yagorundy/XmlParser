#include "element_node.h"

namespace XmlParser {
	ElementNode::ElementNode(const MyString& tag)
		: tag_(tag)
	{ }

	ElementNode::~ElementNode() {
		for (int i = 0; i < children_.getSize(); i++)
			delete children_[i];
	}

	Node* ElementNode::clone() const {
		return new ElementNode(*this);
	}

	void ElementNode::addAttribute(const ElementNodeAttribute& attribute) {
		attributes_.pushBack(attribute);
	}

	void ElementNode::addChild(Node* child) {
		children_.pushBack(child);
	}

	const MyString& ElementNode::getTag() const {
		return tag_;
	}

	const Vector<ElementNodeAttribute>& ElementNode::getAttributes() const {
		return attributes_;
	}

	const Vector<Node*> ElementNode::getChildren() const {
		return children_;
	}

	void ElementNode::pipe(std::ostream& out, int ident) const {
		pipeIdent(out, ident);
		out << '<' << tag_;
		for (int i = 0; i < attributes_.getSize(); i++) {
			out << ' ';
			attributes_[i].pipe(out);
		}
		out << '>';

		if (children_.getSize() == 1 && dynamic_cast<TextNode*>(children_[0]) != nullptr) {
			children_[0]->pipe(out, 0);
			out << '<' << tag_ << "/>";
		}
		else {
			out << std::endl;
			for (int i = 0; i < children_.getSize(); i++) {
				children_[i]->pipe(out, ident + 1);
			}
			pipeIdent(out, ident);
			out << '<' << tag_ << "/>";

		}
		out << std::endl;
	}
}