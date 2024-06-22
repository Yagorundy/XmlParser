#pragma once

#include "node.h"

namespace XmlParser {
	class TextNode : public Node {
		const String text_;

	public:
		TextNode();
		Node* clone() const override;

		const String& getText() const;

		void pipe(std::ostream& out) const override;
	};
}
