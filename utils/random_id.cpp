#include "random_id.h"

namespace XmlParser {
	bool isInit = false;
	unsigned int generateRandomId() {
		if (!isInit) {
			srand(time(NULL));
			isInit = true;
		}
		return rand();
	}
}