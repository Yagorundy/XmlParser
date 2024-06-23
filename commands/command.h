#pragma once

#include "../utils/vector.hpp"
#include "../utils/MyString.h"
#include "../utils/app_exceptions.h"
#include "../app/app_state.h"

namespace XmlParser {
    class Command {
    protected:
        Vector<MyString> args_;

    public:
        static Command* create(const MyString& name, const Vector<MyString>& args);

        Command(Vector<MyString> args);

        virtual void exec(AppState& state) = 0;

        void assertFileOpened(const AppState& state) const;
        void assertFileClosed(const AppState& state) const;
    };
}
