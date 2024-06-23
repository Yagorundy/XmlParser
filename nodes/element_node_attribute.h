#pragma once

#include "../utils/MyString.h"

namespace XmlParser {
    class ElementNodeAttribute {
        MyString name_;
        MyString value_;

    public:
        ElementNodeAttribute();
        ElementNodeAttribute(const MyString& name, const MyString& value);
        ElementNodeAttribute(const ElementNodeAttribute& other);
        ElementNodeAttribute(ElementNodeAttribute&& other) noexcept;
        ElementNodeAttribute& operator=(const ElementNodeAttribute& other);
        ElementNodeAttribute& operator=(ElementNodeAttribute&& other) noexcept;

        const MyString& getName() const;
        const MyString& getValue() const;

        void pipe(std::ostream& out) const;
    };
}
