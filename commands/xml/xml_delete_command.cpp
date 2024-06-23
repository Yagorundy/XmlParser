#include "xml_delete_command.h"

namespace XmlParser {
	const MyString XmlDeleteCommand::kName = "delete";

	XmlDeleteCommand::XmlDeleteCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 2)
			throw InvalidArgumentsException();
	}

	void XmlDeleteCommand::exec(AppState& state) {
		assertFileOpened(state);

		MyString id = args_[0];
		MyString key = args_[1];

		ElementNode* el = state.elementNodeById[id];
		if (el == nullptr)
			return;

		el->removeAttribute(key);
		if (key == "id") {
			state.elementNodeById.remove(id);
		}
	}
}