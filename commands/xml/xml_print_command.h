#pragma once

#include "../command.h"

namespace XmlParser {
    class XmlPrintCommand : public Command {
    public:
        static const MyString kName;

        XmlPrintCommand(Vector<MyString> args);

        void exec(AppState& state) override;
    };
}