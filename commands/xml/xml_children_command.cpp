#include "xml_children_command.h"

namespace XmlParser {
	const MyString XmlChildrenCommand::kName = "children";

	XmlChildrenCommand::XmlChildrenCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 1)
			throw InvalidArgumentsException();
	}

	void XmlChildrenCommand::exec(AppState& state) {
		assertFileOpened(state);

		MyString id = args_[0];

		ElementNode* el = state.elementNodeById[id];
		if (el == nullptr) return;
		
		// a set would be the better solution, but I won't bother to implement it
		Map<MyString, bool> map;
		for (int i = 0; i < el->getChildren().getSize(); i++) {
			ElementNode* elementNodeChild = dynamic_cast<ElementNode*>(el->getChildren()[i]);
			if (elementNodeChild != nullptr) {
				for (int j = 0; j < elementNodeChild->getAttributes().getSize(); j++) {
					map.set(elementNodeChild->getAttributes()[j].getName(), true);
				}
			}
		}

		for (int i = 0; i < map.getEntries().getSize(); i++) {
			std::cout << map.getEntries()[i].key << ' ';
		}
		std::cout << std::endl;
	}
}