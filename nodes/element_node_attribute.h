#pragma once

#include "../utils/string.h"

namespace XmlParser {
    class ElementNodeAttribute {
        String name_;
        String value_;

    public:
        ElementNodeAttribute();
        ElementNodeAttribute(const String& name, const String& value);
        ElementNodeAttribute(const ElementNodeAttribute& other);
        ElementNodeAttribute(ElementNodeAttribute&& other) noexcept;
        ElementNodeAttribute& operator=(const ElementNodeAttribute& other);
        ElementNodeAttribute& operator=(ElementNodeAttribute&& other) noexcept;

        const String& getName() const;
        const String& getValue() const;

        void pipe(std::ostream& out) const;
    };
}
