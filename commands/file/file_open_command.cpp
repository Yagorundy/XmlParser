#include "file_open_command.h"

namespace XmlParser {
    const String FileOpenCommand::kName = "open";

    FileOpenCommand::FileOpenCommand(Vector<String> args)
        : Command(args)
    {
        if (args.getSize() != 1)
            throw InvalidArgumentsException();
    }

    void FileOpenCommand::exec(AppState& state) {
        assertFileClosed(state);

        // TODO: parse xml and construct root node
    }
}