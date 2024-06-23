#include "file_open_command.h"

namespace XmlParser {
    const MyString FileOpenCommand::kName = "open";

    FileOpenCommand::FileOpenCommand(Vector<MyString> args)
        : Command(args)
    {
        if (args.getSize() != 1)
            throw InvalidArgumentsException();
    }

    void FileOpenCommand::exec(AppState& state) {
        assertFileClosed(state);

        MyString path = args_[0];
        std::ifstream file(path.c_str());
        if (!file.is_open()) {
            throw ValidationException((MyString("Failed to open file: ") + path).c_str());
        }

        try {
            XmlParser xmlParser;
            ElementNode* rootNode = xmlParser.parse(file);

            Map<MyString, ElementNode*> elementNodeById;
            xmlParser.assignUniqueIdsAndFillMap(elementNodeById, rootNode);

            state.filePath = path;
            state.rootNode = rootNode;
            state.elementNodeById = elementNodeById;
        }
        catch (...) {
            file.close();
            throw;
        }
    }
}