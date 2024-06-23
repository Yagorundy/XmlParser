#pragma once

#include "node.h"
#include "element_node_attribute.h"
#include "../utils/vector.hpp"
#include "text_node.h"

namespace XmlParser {
	class ElementNode : public Node {
		const MyString tag_;
		Vector<ElementNodeAttribute> attributes_;
		Vector<Node*> children_;

		void setAttribute(const ElementNodeAttribute& attribute, const int& pos);

	public:
		ElementNode(const MyString& tag);
		~ElementNode();
		Node* clone() const override;

		const MyString& getTag() const;

		const Vector<ElementNodeAttribute>& getAttributes() const;
		MyString getAttributeValue(const MyString& name) const;
		void setAttribute(const ElementNodeAttribute& attribute);

		MyString getId() const;
		void setId(const MyString& id);

		const Vector<Node*> getChildren() const;
		void addChild(Node* child);

		void pipe(std::ostream& out, int ident) const override;
	};
}
