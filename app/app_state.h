#pragma once

#include "../utils/MyString.h";
#include "../nodes/element_node.h"
#include "../utils/app_exceptions.h"
#include "../utils/map.hpp"

namespace XmlParser {
	class AppState {
		void copyFrom(const AppState& other);
		void free();
		
	public:
		MyString filePath;
		ElementNode* rootNode;
		Map<MyString, ElementNode*> elementNodeById;
		
		AppState();
		AppState(const AppState&);
		AppState& operator=(const AppState& other);
		~AppState();

		const bool& hasOpenedFile() const;
	};
}