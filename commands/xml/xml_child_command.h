#pragma once

#include "../command.h"
#include "../../utils/map.hpp"
#include "../../utils/number_helpers.h"

namespace XmlParser {
    class XmlChildCommand : public Command {
    public:
        static const MyString kName;

        XmlChildCommand(Vector<MyString> args);

        void exec(AppState& state) override;
    };
}