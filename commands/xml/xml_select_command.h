#pragma once

#include "../command.h"

namespace XmlParser {
    class XmlSelectCommand : public Command {
    public:
        static const MyString kName;

        XmlSelectCommand(Vector<MyString> args);

        void exec(AppState& state) override;
    };
}