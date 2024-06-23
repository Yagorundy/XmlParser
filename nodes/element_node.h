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

	public:
		ElementNode(const MyString& tag);
		~ElementNode();
		Node* clone() const override;

		const MyString& getTag() const;
		void addAttribute(const ElementNodeAttribute& attribute);
		void addAttribute(const MyString& name, const MyString& value);
		void addChild(Node* child);
		
		const Vector<ElementNodeAttribute>& getAttributes() const;
		const Vector<Node*> getChildren() const;
		
		MyString getId() const;
		void setId(const MyString& id);

		void pipe(std::ostream& out, int ident) const override;
	};
}
