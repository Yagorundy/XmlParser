#pragma once

#include "../command.h"
#include "../../utils/map.hpp"

namespace XmlParser {
    class XmlChildrenCommand : public Command {
    public:
        static const MyString kName;

        XmlChildrenCommand(Vector<MyString> args);

        void exec(AppState& state) override;
    };
}