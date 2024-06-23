#pragma once

#include "../command.h"

namespace XmlParser {
    class XmlNewchildCommand : public Command {
    public:
        static const MyString kName;

        XmlNewchildCommand(Vector<MyString> args);

        void exec(AppState& state) override;
    };
}