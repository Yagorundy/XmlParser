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

		MyString xPath = args_[0];

		Vector<MyString> tokens = xPath.split('/');

		//for (int i = 0; i < tokens.getSize(); i++) {
		//	std::cout << tokens[i] << ' ';
		//}
		//std::cout << std::endl;

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
				expression = token.substr(openingBracketIndex + 1, token.getSize() - (openingBracketIndex + 1) - 2);
			}
			
			// handle index expression
			int indexExpression = -1;
			try {
				indexExpression = parseInt(expression.c_str()) - 1;
			} catch (ValidationException _) { }

			//std::cout << "__ " << tag << ' ' << expression << std::endl;

			Vector<ElementNode*> m;
			for (int j = 0; j < parents.getSize(); j++) {
				ElementNode* parent = parents[j];

				int currIndexExpression = indexExpression;
				for (int k = 0; k < parent->getChildren().getSize(); k++) {
					ElementNode* child = dynamic_cast<ElementNode*>(parent->getChildren()[k]);
					if (child == nullptr)
						continue;

					if (child->getTag() == tag) {
						// index expression case
						if (indexExpression != -1) {
							if (currIndexExpression > 0) {
								currIndexExpression--;
							}
							else {
								m.pushBack(child);
								break;
							}
						}
						// default case
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

		for (int i = 0; i < parents.getSize(); i++) {
			parents[i]->pipeInnerText(std::cout);
		}
	}
}