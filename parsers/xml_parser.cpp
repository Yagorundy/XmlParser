#include "xml_parser.h"

namespace XmlParser {

	ElementNode* XmlParser::parse(std::istream& in) {
		// TODO: free memory in case of thrown exception

		readUntil(in, '<');
		MyString rootTagContent = readUntil(in, '>');
		rootTagContent = rootTagContent.trim();
		if (rootTagContent.empty()) {
			throw ValidationException("Invalid XML format: Empty tag.");
		}

		return parseElement(in, rootTagContent, true);
	}

	ElementNode* XmlParser::parseElement(std::istream& file, const MyString& openingTagContent, bool isRoot) {
		//std::cout << "openingTagContent: " << openingTagContent << std::endl;

		// !NOTE - opening tag content can be parsed just like command line arguments
		ArgumentParser argsParser;
		Vector<MyString> args = argsParser.parse(openingTagContent);

		MyString tag = args[0];
		args.popFront();

		ElementNode* element = new ElementNode(tag);

		try {
			for (int i = 0; i < args.getSize(); i++) {
				element->setAttribute(parseAttribute(args[i]));
			}

			// parse element content
			while (file.good()) {
				MyString text = readUntil(file, '<');
				text = text.trim();
				//std::cout << "Found text with length " << text.getSize() << ": " << text << std::endl;
				if (!text.empty()) {
					element->addChild(new TextNode(text));
				}

				// closing tag
				if (file.peek() == '/') {
					file.seekg(1, std::ios::cur);

					MyString closingTag = readUntil(file, '>');
					closingTag = closingTag.trim();

					if (closingTag != tag) {
						delete element;
						throw ValidationException((MyString("Mismatched closing tag: ") + closingTag).c_str());
					}
					break;
				}
				// nested element
				else {
					MyString nestedTagContent = readUntil(file, '>');
					nestedTagContent = nestedTagContent.trim(); // Remove leading and trailing whitespace
					if (nestedTagContent.empty()) {
						throw ValidationException("Invalid XML format: Empty tag.");
					}

					element->addChild(parseElement(file, nestedTagContent, false));
				}
			}

			return element;
		}
		catch (...) {
			if (isRoot)
				delete element;
			throw;
		}
	}

	ElementNodeAttribute XmlParser::parseAttribute(const MyString& attribute) {
		int eqIndex = attribute.find('=', 0);
		if (eqIndex == -1) {
			throw ValidationException("Invalid attribute format: no '=' found");
		}

		MyString name = attribute.substr(0, eqIndex).trim();
		if (name.empty()) {
			throw ValidationException("Invalid attribute format: empty attribute name");
		}

		char quoteChar = attribute[eqIndex + 1];
		if (quoteChar != '"' && quoteChar != '\'') {
			throw ValidationException("Invalid attribute format: no opening quote for attribute value");
		}

		int valueStart = eqIndex + 2;
		int valueEnd = attribute.find(quoteChar, valueStart);
		if (valueEnd == -1) {
			throw ValidationException("Invalid attribute format: no closing quote for attribute value");
		}

		MyString value = attribute.substr(valueStart, valueEnd - valueStart).trim();
		return ElementNodeAttribute(name, value);
	}

	MyString XmlParser::readUntil(std::istream& is, char delimiter) {
		MyString result;
		char ch;
		while (is.get(ch)) {
			if (ch == delimiter) {
				break;
			}
			result += ch;
		}
		return result;
	}

	void XmlParser::assignUniqueIdsAndFillMap(Map<MyString, ElementNode*>& elementNodeById, ElementNode* node) {
		MyString id = node->getId();
		if (id.empty()) {
			do {
				id = generateRandomId();
			} while (elementNodeById.contains(id));
		}
		else if (elementNodeById.contains(id)) {
			MyString extendedId;
			do {
				extendedId = id + "_" + generateRandomId();
			} while (elementNodeById.contains(extendedId));
			id = extendedId;
		}

		node->setId(id);
		elementNodeById.set(id, node);

		for (int i = 0; i < node->getChildren().getSize(); i++) {
			ElementNode* elementNodeChild = dynamic_cast<ElementNode*>(node->getChildren()[i]);
			if (elementNodeChild != nullptr) {
				assignUniqueIdsAndFillMap(elementNodeById, elementNodeChild);
			}
		}
	}

}
