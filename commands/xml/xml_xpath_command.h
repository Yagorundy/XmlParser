#pragma once

#include "../command.h"
#include "../../utils/number_helpers.h"

namespace XmlParser {
    class XmlXpathCommand : public Command {
    public:
        static const MyString kName;

        XmlXpathCommand(Vector<MyString> args);

        void exec(AppState& state) override;
    };
}