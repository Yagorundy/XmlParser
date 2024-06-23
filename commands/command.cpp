#include "command.h"
#include "file/file_open_command.h"
#include "xml/xml_print_command.h"
#include "file/file_save_command.h"
#include "file/file_close_command.h"

namespace XmlParser {
    Command::Command(Vector<MyString> args)
        : args_(args)
    { }

    Command* Command::create(const MyString& name, const Vector<MyString>& args) {
        if (name == FileOpenCommand::kName)
            return new FileOpenCommand(args);
        if (name == FileSaveCommand::kName)
            return new FileSaveCommand(args);
        if (name == FileCloseCommand::kName)
            return new FileCloseCommand(args);
        if (name == XmlPrintCommand::kName)
            return new XmlPrintCommand(args);
        throw ValidationException("Unrecognized command!");
    }

    void Command::assertFileOpened(const AppState& state) const {
        if (!state.hasOpenedFile())
            throw ValidationException("There is no file opened!");
    }

    void Command::assertFileClosed(const AppState& state) const {
        if (state.hasOpenedFile())
            throw ValidationException("There is already a file opened!");
    }
}