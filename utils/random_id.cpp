#include "random_id.h"

namespace XmlParser {
	/* Inspiration came from internet */
	bool isInit_ = false;
	unsigned int generateRandomNumber() {
		if (!isInit_) {
			srand(time(NULL));
			isInit_ = true;
		}
		return rand();
	}

	MyString generateRandomId() {
		int num = generateRandomNumber();
		MyString result;
		while (num > 0) {
			result += ('0' + num % 10);
			num /= 10;
		}
		return result;
	}
}