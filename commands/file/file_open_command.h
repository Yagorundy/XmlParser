#pragma once

#include "../command.h"
#include "../../utils/string.h"
#include "../../app/app_state.h"

namespace XmlParser {
    class FileOpenCommand : public Command {
    public:
        static const String kName;

        FileOpenCommand(Vector<String> args);

        virtual void exec(AppState& state);
    };
}