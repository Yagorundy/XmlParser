#include "xml_text_command.h"

namespace XmlParser {
	const MyString XmlTextCommand::kName = "text";

	XmlTextCommand::XmlTextCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 1)
			throw InvalidArgumentsException();
	}

	void XmlTextCommand::exec(AppState& state) {
		assertFileOpened(state);

		MyString id = args_[0];

		ElementNode* el = state.elementNodeById[id];
		if (el == nullptr) return;

		el->pipe(std::cout, 0);
		std::cout << std::endl;
	}
}