#include "app_state.h"

namespace XmlParser {
	void AppState::copyFrom(const AppState& other) {
		filePath = other.filePath;
		rootNode = dynamic_cast<ElementNode*>(other.rootNode->clone());
		// TODO: fix
		elementNodeById = other.elementNodeById;
	}
	void AppState::free() {
		delete rootNode;
	}

	AppState::AppState(): rootNode(nullptr) { }

	AppState::AppState(const AppState& other) {
		copyFrom(other);
	}

	AppState& AppState::operator=(const AppState& other) {
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}

	AppState::~AppState() {
		free();
	}

	const bool& AppState::hasOpenedFile() const {
		return filePath.getSize() != 0;
	}
}