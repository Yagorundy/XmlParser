#pragma once

#include "../command.h"
#include "../../utils/string.h"
#include "../../app/app_state.h"

namespace XmlParser {
    class XmlPrintCommand : public Command {
    public:
        static const String kName;

        XmlPrintCommand(Vector<String> args);

        void exec(AppState& state) override;
    };
}