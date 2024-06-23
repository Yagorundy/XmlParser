#pragma once

#include "../command.h"

namespace XmlParser {
    class XmlSetCommand : public Command {
    public:
        static const MyString kName;

        XmlSetCommand(Vector<MyString> args);

        void exec(AppState& state) override;
    };
}