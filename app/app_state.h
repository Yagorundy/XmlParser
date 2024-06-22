#pragma once

#include "../utils/string.h";
#include "../nodes/element_node.h"
#include "../utils/app_exceptions.h"

namespace XmlParser {
	class AppState {
		String filePath_;
		ElementNode* rootNode_;

		void copyFrom(const AppState& other);
		void free();

	public:
		AppState();
		AppState(const AppState&);
		AppState& operator=(const AppState& other);
		~AppState();

		String& getFilePath();
		ElementNode* getRootNode();
		const bool& hasOpenedFile() const;
	};
}