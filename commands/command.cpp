#include "command.h"
#include "file/file_open_command.h"
#include "xml/xml_print_command.h"

namespace XmlParser {
    Command::Command(Vector<String> args)
        : args_(args)
    { }

    Command* Command::create(const String& name, const Vector<String>& args) {
        if (name == FileOpenCommand::kName)
            return new FileOpenCommand(args);
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