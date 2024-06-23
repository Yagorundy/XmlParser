#pragma once

#include "../command.h"

namespace XmlParser {
    class XmlDeleteCommand : public Command {
    public:
        static const MyString kName;

        XmlDeleteCommand(Vector<MyString> args);

        void exec(AppState& state) override;
    };
}