#pragma once

#include <iostream>
#include "../nodes/node.h"
#include "../nodes/element_node.h"
#include "../nodes/text_node.h"
#include "../utils/MyString.h"
#include "../utils/vector.hpp"
#include "../utils/app_exceptions.h"
#include "argument_parser.h"
#include "../utils/random_id.h"
#include "../utils/map.hpp"

namespace XmlParser {
    class XmlParser {
    public:
        ElementNode* parse(std::istream& is);
        void assignUniqueIdsAndFillMap(Map<MyString, ElementNode*>& elementNodeById, ElementNode* node);

    private:
        ElementNode* parseElement(std::istream& in, const MyString& tag);
        ElementNodeAttribute parseAttribute(const MyString& attribute);
        MyString readUntil(std::istream& is, char delimiter);
    };
}
