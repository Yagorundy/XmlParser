#include "element_node.h"

namespace XmlParser {
	ElementNode::ElementNode(const String& tag)
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

	void ElementNode::addChild(const Node* child) {
		//children_.pushBack(child.clone());
	}

	const String& ElementNode::getTag() const {
		return tag_;
	}

	const Vector<ElementNodeAttribute>&  ElementNode::getAttributes() const {
		return attributes_;
	}

	const Vector<Node*> ElementNode::getChildren() const {
		return children_;
	}

	void ElementNode::pipe(std::ostream& out) const {
		out << '<' << tag_ << ' ';
		for (int i = 0; i < attributes_.getSize(); i++) {
			attributes_[i].pipe(out);
			if (i != attributes_.getSize() - 1)
				out << ' ';
		}
		out << '>';

		for (int i = 0; i < children_.getSize(); i++) {
			children_[i]->pipe(out);
		}
		out << '<' << tag_ << "/>";
	}
}