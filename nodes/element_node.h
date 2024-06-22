#pragma once

#include "node.h"
#include "element_node_attribute.h"

namespace XmlParser {
	class ElementNode : public Node {
		const String tag_;
		Vector<ElementNodeAttribute> attributes_;
		Vector<Node*> children_;

	public:
		ElementNode(const String& tag);
		~ElementNode();
		Node* clone() const override;

		const String& getTag() const;
		void addAttribute(const ElementNodeAttribute& attribute);
		void addChild(const Node* child);
		
		const Vector<ElementNodeAttribute>& getAttributes() const;
		const Vector<Node*> getChildren() const;

		void pipe(std::ostream& out) const;
	};
}
