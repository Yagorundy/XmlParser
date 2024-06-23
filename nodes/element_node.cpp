#include "element_node.h"

namespace XmlParser {
	ElementNode::ElementNode(const MyString& tag)
		: tag_(tag)
	{ }

	ElementNode::~ElementNode() {
		for (int i = 0; i < children_.getSize(); i++)
			delete children_[i];
	}

	// TODO: fix
	Node* ElementNode::clone() const {
		return new ElementNode(*this);
	}

	const MyString& ElementNode::getTag() const {
		return tag_;
	}

	const Vector<ElementNodeAttribute>& ElementNode::getAttributes() const {
		return attributes_;
	}

	MyString ElementNode::getAttributeValue(const MyString& name) const {
		for (int i = 0; i < attributes_.getSize(); i++) {
			if (attributes_[i].getName() == name) {
				return attributes_[i].getValue();
			}
		}
		return MyString();
	}

	void ElementNode::setAttribute(const ElementNodeAttribute& attribute, const int& pos) {
		int i = 0;
		for (; i < attributes_.getSize(); i++) {
			if (attributes_[i].getName() == attribute.getName()) {
				break;
			}
		}
		if (i >= attributes_.getSize()) {
			attributes_.pushAt(attribute, pos);
		}
		else {
			attributes_[i].setValue(attribute.getValue());
		}
	}

	void ElementNode::setAttribute(const ElementNodeAttribute& attribute) {
		setAttribute(attribute, attributes_.getSize());
	}

	MyString ElementNode::getId() const {
		return getAttributeValue("id");
	}

	void ElementNode::setId(const MyString& id) {
		setAttribute(ElementNodeAttribute("id", id), 0);
	}

	const Vector<Node*>& ElementNode::getChildren() const {
		return children_;
	}

	void ElementNode::addChild(Node* child) {
		children_.pushBack(child);
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
			out << "</" << tag_ << '>';
		}
		else {
			out << std::endl;
			for (int i = 0; i < children_.getSize(); i++) {
				children_[i]->pipe(out, ident + 1);
				if (dynamic_cast<TextNode*>(children_[i]) != nullptr) {
					out << std::endl;
				}
			}
			pipeIdent(out, ident);
			out << "</" << tag_ << '>';

		}
		out << std::endl;
	}
}