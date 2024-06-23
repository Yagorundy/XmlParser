#pragma once

#include <fstream>
#include "../command.h"
#include "../../parsers/xml_parser.h"

namespace XmlParser {
    class FileOpenCommand : public Command {
    public:
        static const MyString kName;

        FileOpenCommand(Vector<MyString> args);

        virtual void exec(AppState& state);
    };
}