#include "file_save_command.h"

namespace XmlParser {
    const MyString FileSaveCommand::kName = "save";

    FileSaveCommand::FileSaveCommand(Vector<MyString> args)
        : Command(args)
    {
        if (!(args.getSize() == 0 || (args.getSize() == 2 && args[0] == "as")))
            throw InvalidArgumentsException();
    }

    void FileSaveCommand::exec(AppState& state) {
        assertFileOpened(state);

        MyString path = args_.getSize() == 2 ? args_[1] : state.filePath;

        std::ofstream file(path.c_str(), std::ios::trunc);
        if (!file.is_open()) {
            throw ValidationException((MyString("Failed to open file: ") + path).c_str());
        }

        try {
            state.rootNode->pipe(file, 0);
        }
        catch (...) {
            file.close();
            throw;
        }
    }
}