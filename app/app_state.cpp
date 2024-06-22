#include "app_state.h"

namespace XmlParser {
	void AppState::copyFrom(const AppState& other) {
		filePath_ = other.filePath_;
		rootNode_ = dynamic_cast<ElementNode*>(other.rootNode_->clone());
	}
	void AppState::free() {
		delete rootNode_;
	}

	AppState::AppState() { }

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

	String& AppState::getFilePath() {
		return filePath_;
	}

	ElementNode* AppState::getRootNode() {
		return rootNode_;
	}

	const bool& AppState::hasOpenedFile() const {
		return filePath_.getSize() != 0;
	}
}