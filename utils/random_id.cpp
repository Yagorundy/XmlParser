#include "random_id.h"

namespace XmlParser {
	/* Inspiration came from internet */
	bool isInit_ = false;
	unsigned int generateRandomId() {
		if (!isInit_) {
			srand(time(NULL));
			isInit_ = true;
		}
		return rand();
	}
}