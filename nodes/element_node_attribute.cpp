#include "element_node_attribute.h"

namespace XmlParser {
    ElementNodeAttribute::ElementNodeAttribute() : name_(""), value_("") {}

    ElementNodeAttribute::ElementNodeAttribute(const String& name, const String& value)
        : name_(name), value_(value) {}

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

    const String& ElementNodeAttribute::getName() const {
        return name_;
    }

    const String& ElementNodeAttribute::getValue() const {
        return value_;
    }

    void ElementNodeAttribute::pipe(std::ostream& out) const {
        out << name_ << '=' << '"' << value_ << '"';
    }
}