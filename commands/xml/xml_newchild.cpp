#include "xml_newchild_command.h"

namespace XmlParser {
	const MyString XmlNewchildCommand::kName = "newchild";

	XmlNewchildCommand::XmlNewchildCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 2)
			throw InvalidArgumentsException();
	}

	void XmlNewchildCommand::exec(AppState& state) {
		assertFileOpened(state);

		MyString id = args_[0];
		MyString tag = args_[1];

		ElementNode* el = state.elementNodeById[id];
		if (el == nullptr)
			return;

		ElementNode* child = new ElementNode(tag);
		child->setId(generateRandomId());

		el->addChild(child);
		state.elementNodeById[el->getId()] = el;
	}
}