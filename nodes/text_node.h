#pragma once

#include "node.h"
#include "../utils/MyString.h"

namespace XmlParser {
	class TextNode : public Node {
		const MyString text_;		

	public:
		TextNode();
		TextNode(const MyString& text);
		Node* clone() const override;

		const MyString& getText() const;

		void pipe(std::ostream& out, int ident) const override;
	};
}
