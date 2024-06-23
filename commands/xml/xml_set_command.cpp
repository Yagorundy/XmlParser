#include "xml_set_command.h"

namespace XmlParser {
	const MyString XmlSetCommand::kName = "set";

	XmlSetCommand::XmlSetCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 3)
			throw InvalidArgumentsException();
	}

	void XmlSetCommand::exec(AppState& state) {
		assertFileOpened(state);

		MyString id = args_[0];
		MyString key = args_[1];
		MyString value = args_[2];

		ElementNode* el = state.elementNodeById[id];
		if (el == nullptr)
			return;

		el->setAttribute(ElementNodeAttribute(key, value));
		if (key == "id") {
			state.elementNodeById.remove(id);
			state.elementNodeById[value] = el;
		}
	}
}