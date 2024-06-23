#include "command.h"
#include "file/file_open_command.h"
#include "file/file_save_command.h"
#include "file/file_close_command.h"
#include "xml/xml_print_command.h"
#include "xml/xml_select_command.h"
#include "xml/xml_set_command.h"
#include "xml/xml_children_command.h"
#include "xml/xml_child_command.h"
#include "xml/xml_text_command.h"
#include "xml/xml_delete_command.h"
#include "xml/xml_newchild_command.h"

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
        if (name == XmlSelectCommand::kName)
            return new XmlSelectCommand(args);
        if (name == XmlSetCommand::kName)
            return new XmlSetCommand(args);
        if (name == XmlChildrenCommand::kName)
            return new XmlChildrenCommand(args);
        if (name == XmlChildCommand::kName)
            return new XmlChildCommand(args);
        if (name == XmlTextCommand::kName)
            return new XmlTextCommand(args);
        if (name == XmlDeleteCommand::kName)
            return new XmlDeleteCommand(args);
        if (name == XmlNewchildCommand::kName)
            return new XmlNewchildCommand(args);
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