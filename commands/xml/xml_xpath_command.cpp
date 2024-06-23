#include "xml_xpath_command.h"

namespace XmlParser {
	const MyString XmlXpathCommand::kName = "xpath";

	XmlXpathCommand::XmlXpathCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 1)
			throw InvalidArgumentsException();
	}

	void XmlXpathCommand::exec(AppState& state) {
		//assertFileOpened(state);

		MyString query = args_[0];
		MyString fun;
		MyString xPath;

		// quick check for function (could have many edge case bugs)
		int funBracketIndex = query.find('(', 0);
		if (funBracketIndex != -1) {
			fun = query.substr(0, funBracketIndex);
			int xPathStart = funBracketIndex + 1;
			int xPathEnd = query.find(')', xPathStart);
			if (xPathEnd == -1) {
				throw ValidationException("Invalid expression format: no closing bracket");
			}
			xPath = query.substr(xPathStart, xPathEnd - xPathStart);
		}
		else {
			xPath = query;
		}

		Vector<MyString> tokens = xPath.split('/');

		//for (int i = 0; i < tokens.getSize(); i++) {
		//	std::cout << tokens[i] << ' ';
		//}
		//std::cout << std::endl;

		Vector<ElementNode*> result = evalXpath(tokens, state);

		if (fun.empty()) {
			for (int i = 0; i < result.getSize(); i++) {
				result[i]->pipeInnerText(std::cout);
			}
		}
		else if (fun == "count") {
			std::cout << result.getSize();
			std::cout << std::endl;
		}
		
	}

	Vector<ElementNode*> XmlXpathCommand::evalXpath(const Vector<MyString>& tokens, AppState& state) {
		// since we look at the structure from the parent prespective, we need to wrap our root into another node
		ElementNode root("");
		root.addChild(state.rootNode);

		Vector<ElementNode*> parents; // matching parents
		parents.pushBack(&root);

		for (int i = 0; i < tokens.getSize(); i++) {
			MyString token = tokens[i];
			MyString tag;
			MyString expression;

			// parse token into tag and expression
			int openingBracketIndex = token.find('[', 0);
			if (openingBracketIndex == -1) {
				tag = token;
			}
			else {
				tag = token.substr(0, openingBracketIndex);
				int exprStart = openingBracketIndex + 1;
				int exprEnd = token.find(']', exprStart);
				if (exprEnd == -1) {
					throw ValidationException("Invalid expression format: no closing bracket");
				}
				expression = token.substr(exprStart, exprEnd - exprStart);
			}

			// handle index expression
			int index = -1;
			if (!expression.empty()) {
				try {
					index = parseInt(expression.c_str()) - 1;
				}
				catch (ValidationException _) {}
			}

			// handle attribute and child tag expressions
			MyString attribute;
			MyString childTag;
			MyString compareValue;
			if (!expression.empty()) {
				int eqIndex = expression.find('=', 0);
				if (expression[0] == '@') {
					if (eqIndex == -1) {
						attribute = expression.substr(1);
					}
					else {
						attribute = expression.substr(1, eqIndex - 1);
					}
				}
				else {
					if (eqIndex == -1) {
						childTag = expression;
					}
					else {
						childTag = expression.substr(0, eqIndex);
					}
				}
				if (eqIndex != -1) {
					char quoteChar = expression[eqIndex + 1];
					if (quoteChar != '"' && quoteChar != '\'') {
						throw ValidationException("Invalid expression format: no opening quote for expression value");
					}

					int valueStart = eqIndex + 2;
					int valueEnd = expression.find(quoteChar, valueStart);
					if (valueEnd == -1) {
						throw ValidationException("Invalid expression format: no closing quote for expression value");
					}

					compareValue = expression.substr(valueStart, valueEnd - valueStart).trim();
				}
			}

			//std::cout << "__ " << tag << ' ' << expression << std::endl;

			Vector<ElementNode*> m;
			for (int j = 0; j < parents.getSize(); j++) {
				ElementNode* parent = parents[j];

				int currIndex = index;
				for (int k = 0; k < parent->getChildren().getSize(); k++) {
					ElementNode* child = dynamic_cast<ElementNode*>(parent->getChildren()[k]);
					if (child == nullptr)
						continue;

					// match tag
					if (child->getTag() == tag) {
						// index expression case
						if (index != -1) {
							if (currIndex > 0) {
								currIndex--;
							}
							else {
								m.pushBack(child);
								break;
							}
						}
						// attribute expression
						else if (!attribute.empty()) {
							if (compareValue.empty()) {
								if (child->containsAttribute(attribute)) {
									m.pushBack(child);
								}
							}
							else {
								if (child->getAttributeValue(attribute) == compareValue) {
									m.pushBack(child);
								}
							}
						}
						// child tag
						else if (!childTag.empty()) {
							for (int x = 0; x < child->getChildren().getSize(); x++) {
								ElementNode* gChild = dynamic_cast<ElementNode*>(child->getChildren()[x]);
								if (gChild != nullptr && gChild->getTag() == childTag) {
									if (compareValue.empty()) {
										m.pushBack(child);
										break;
									}
									else {
										TextNode* ggChild = gChild->getChildren().getSize() == 1
											? dynamic_cast<TextNode*>(gChild->getChildren()[0])
											: nullptr;
										if (ggChild != nullptr && ggChild->getText() == compareValue) {
											m.pushBack(child);
											break;
										}
									}
								}
							}
						}
						// no expression
						else {
							m.pushBack(child);
						}
					}
				}
			}

			parents = m;
		}

		// remove state.rootNode so root destructor doesn't wipe
		root.dropChild(0);

		return parents;
	}
}