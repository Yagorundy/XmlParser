#include "xml_select_command.h"

namespace XmlParser {
	const MyString XmlSelectCommand::kName = "select";

	XmlSelectCommand::XmlSelectCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 2)
			throw InvalidArgumentsException();
	}

	void XmlSelectCommand::exec(AppState& state) {
		assertFileOpened(state);
		
		MyString id = args_[0];
		MyString key = args_[1];

		ElementNode* el = state.elementNodeById[id];
		if (el != nullptr) {
			std::cout << el->getAttributeValue(key);
		}
		std::cout << std::endl;
	}
}