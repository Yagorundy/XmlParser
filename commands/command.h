#pragma once

#include "../utils/vector.hpp"
#include "../utils/string.h"
#include "../utils/app_exceptions.h"
#include "../app/app_state.h"

namespace XmlParser {
    class Command {
    protected:
        Vector<String> args_;

    public:
        static Command* create(const String& name, const Vector<String>& args);

        Command(Vector<String> args);

        virtual void exec(AppState& state) = 0;

        void assertFileOpened(const AppState& state) const;
        void assertFileClosed(const AppState& state) const;
    };
}
