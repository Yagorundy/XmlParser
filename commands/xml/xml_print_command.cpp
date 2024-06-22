#include "xml_print_command.h"

namespace XmlParser {
	const String XmlPrintCommand::kName = "print";

	XmlPrintCommand::XmlPrintCommand(Vector<String> args)
		: Command(args)
	{
		if (args.getSize() != 0)
			throw InvalidArgumentsException();
	}

	void XmlPrintCommand::exec(AppState& state) {
		assertFileOpened(state);
		state.getRootNode()->pipe(std::cout);
	}
}