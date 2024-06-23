#pragma once

#include <fstream>
#include "../command.h"
#include "../../parsers/xml_parser.h"

namespace XmlParser {
    class FileSaveCommand : public Command {
    public:
        static const MyString kName;

        FileSaveCommand(Vector<MyString> args);

        virtual void exec(AppState& state);
    };
}