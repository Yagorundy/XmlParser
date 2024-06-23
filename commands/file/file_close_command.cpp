#include "file_close_command.h"

namespace XmlParser {
    const MyString FileCloseCommand::kName = "close";

    FileCloseCommand::FileCloseCommand(Vector<MyString> args)
        : Command(args)
    {
        if (args.getSize() != 0)
            throw InvalidArgumentsException();
    }

    void FileCloseCommand::exec(AppState& state) {
        assertFileOpened(state);
        state.clear();
    }
}