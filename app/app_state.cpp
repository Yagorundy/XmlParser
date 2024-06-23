#include "app_state.h"

namespace XmlParser {
	void AppState::copyFrom(const AppState& other) {
		filePath = other.filePath;
		rootNode = dynamic_cast<ElementNode*>(other.rootNode->clone());

		XmlParser xmlParser;
		xmlParser.assignUniqueIdsAndFillMap(elementNodeById, rootNode);
	}
	void AppState::clear() {
		filePath = MyString();
		delete rootNode;
		elementNodeById = Map<MyString, ElementNode*>();
	}

	AppState::AppState(): rootNode(nullptr) { }

	AppState::AppState(const AppState& other) {
		copyFrom(other);
	}

	AppState& AppState::operator=(const AppState& other) {
		if (this != &other)
		{
			clear();
			copyFrom(other);
		}
		return *this;
	}

	AppState::~AppState() {
		clear();
	}

	const bool& AppState::hasOpenedFile() const {
		return filePath.getSize() != 0;
	}
}