#include "xml_child_command.h"

namespace XmlParser {
	const MyString XmlChildCommand::kName = "child";

	XmlChildCommand::XmlChildCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 2)
			throw InvalidArgumentsException();
	}

	void XmlChildCommand::exec(AppState& state) {
		assertFileOpened(state);

		MyString id = args_[0];
		int n = parseInt(args_[1].c_str());

		ElementNode* el = state.elementNodeById[id];
		if (el == nullptr) return;

		int index = n - 1;
		if (index < el->getChildren().getSize()) {
			el->getChildren()[index]->pipe(std::cout, 0);
		}
		std::cout << std::endl;
	}
}