#pragma once

#include "../utils/MyString.h";
#include "../nodes/element_node.h"
#include "../utils/app_exceptions.h"

namespace XmlParser {
	class AppState {
		MyString filePath_;
		ElementNode* rootNode_;

		void copyFrom(const AppState& other);
		void free();

	public:
		AppState();
		AppState(const AppState&);
		AppState& operator=(const AppState& other);
		~AppState();

		MyString getFilePath() const;
		void setFilePath(const MyString& path);

		ElementNode* getRootNode() const;
		void setRootNode(ElementNode* node);

		const bool& hasOpenedFile() const;
	};
}