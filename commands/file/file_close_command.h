#pragma once

#include <fstream>
#include "../command.h"
#include "../../parsers/xml_parser.h"

namespace XmlParser {
    class FileCloseCommand : public Command {
    public:
        static const MyString kName;

        FileCloseCommand(Vector<MyString> args);

        virtual void exec(AppState& state);
    };
}