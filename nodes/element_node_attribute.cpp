#include "element_node_attribute.h"

namespace XmlParser {
    ElementNodeAttribute::ElementNodeAttribute() { }

    ElementNodeAttribute::ElementNodeAttribute(const MyString& name, const MyString& value)
        : name_(name), value_(value)
    { }

    ElementNodeAttribute::ElementNodeAttribute(const ElementNodeAttribute& other)
        : name_(other.name_), value_(other.value_) {}

    ElementNodeAttribute::ElementNodeAttribute(ElementNodeAttribute&& other) noexcept
        : name_(std::move(other.name_)), value_(std::move(other.value_)) {}

    ElementNodeAttribute& ElementNodeAttribute::operator=(const ElementNodeAttribute& other) {
        if (this != &other) {
            name_ = other.name_;
            value_ = other.value_;
        }
        return *this;
    }

    ElementNodeAttribute& ElementNodeAttribute::operator=(ElementNodeAttribute&& other) noexcept {
        if (this != &other) {
            name_ = std::move(other.name_);
            value_ = std::move(other.value_);
        }
        return *this;
    }

    const MyString& ElementNodeAttribute::getName() const {
        return name_;
    }

    const MyString& ElementNodeAttribute::getValue() const {
        return value_;
    }

    void ElementNodeAttribute::pipe(std::ostream& out) const {
        out << name_ << '=' << '"' << value_ << '"';
    }
}
