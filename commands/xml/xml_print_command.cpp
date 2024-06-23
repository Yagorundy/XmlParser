#include "xml_print_command.h"

namespace XmlParser {
	const MyString XmlPrintCommand::kName = "print";

	XmlPrintCommand::XmlPrintCommand(Vector<MyString> args)
		: Command(args)
	{
		if (args.getSize() != 0)
			throw InvalidArgumentsException();
	}

	void XmlPrintCommand::exec(AppState& state) {
		assertFileOpened(state);
		state.rootNode->pipe(std::cout, 0);
	}
}