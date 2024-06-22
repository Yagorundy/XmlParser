/* copied from https://github.com/Yagorundy/SVG/blob/master/src/utils/string.cpp */

#include "string.h"

#pragma warning(disable : 4996)

void String::copyFrom(const String& other)
{
	str_ = new char[strlen(other.str_) + 1];
	strcpy(str_, other.str_);
	size_ = other.size_;
}
void String::free()
{
	delete[] str_;
}

String::String()
{
	str_ = new char[1];
	str_[0] = '\0';
	size_ = 0;
}

String::String(const char* data)
{
	if (data == nullptr)
	{
		str_ = new char[1];
		str_[0] = '\0';
		size_ = 0;
	}
	else
	{
		size_ = strlen(data);
		str_ = new char[size_ + 1];
		strcpy(str_, data);
	}
}

String::String(const String& other)
{
	copyFrom(other);
}
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
String::~String()
{
	free();
}


size_t String::getSize() const
{
	return size_;
}
void String::concat(const String& other)
{
	char* temp = new char[getSize() + other.getSize() + 1];
	strcpy(temp, str_);
	strcat(temp, other.str_);

	delete[] str_;
	str_ = temp;
	size_ = size_ + other.getSize();
}

char& String::operator[](const size_t index) {
	if (index < 0 || index >= size_)
		throw "Invalid index";

	return str_[index];
}

const char& String::operator[](const size_t index) const {
	if (index < 0 || index >= size_)
		throw "Invalid index";

	return str_[index];
}

const char* String::c_str() const
{
	return str_;
}

String& String::operator+=(const String& other)
{
	concat(other);
	return *this;
}

void String::getLine(std::istream& outFile)
{
	delete[] str_;
	char buff[1024];

	outFile.getline(buff, 1024, '\n');
	size_t len = strlen(buff);
	str_ = new char[len + 1];
	for (size_t i = 0; i < len; i++)
		str_[i] = buff[i];
	str_[len] = '\0';
	size_ = len;
}

String String::trim() const {
	int start = 0;
	while (isspace(str_[start]) && start < size_) start++;

	if (start == size_)
		return String();

	int end = size_ - 1;
	while (isspace(end) && end > start) end--;

	return substring(start, end + 1);
}

String String::substring(int start) const {
	return substring(start, size_);
}

String String::substring(int start, int end) const {
	if (start < 0 || start >= size_ || end < 0 || start > end)
		throw "Invalid substring args";
	int len = end - start;
	String result;
	if (len == 0)
		return result;

	result.free();
	result.str_ = new char[len + 1];
	for (int i = 0; i < len; i++) {
		result.str_[i] = str_[i + start];
	}
	result.str_[len] = '\0';
	result.size_ = len;
	return result;
}

Vector<String> String::split(const char& delim) const {
	Vector<String> result;
	int start = 0;
	bool inToken = str_[0] != delim;
	for (int i = 0; i < size_; i++) {
		bool isDelim = str_[i] == delim;
		bool isEnd = i == size_ - 1;

		if (isDelim) {
			if (inToken) {
				result.pushBack(substring(start, i));
				inToken = false;
			}
			else {
				// ...
			}
		}
		else {
			if (inToken) {
				// ...
			}
			else {
				start = i;
				inToken = true;
			}
		}

		if (isEnd && inToken) {
			result.pushBack(substring(start));
		}
	}
	return result;
}


String operator+(const String& lhs, const String& rhs)
{
	String copyOfLeft(lhs);
	copyOfLeft += rhs;
	return copyOfLeft;
}

std::ostream& operator<<(std::ostream& stream, const String& str)
{
	stream << str.str_;
	return stream;
}

std::istream& operator>>(std::istream& stream, String& str)
{
	delete[] str.str_;
	char buff[1024];
	stream >> buff;

	str.size_ = strlen(buff);
	str.str_ = new char[str.size_ + 1];
	strcpy(str.str_, buff);

	return stream;
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator==(const String& lhs, const char* rhs) {
	return strcmp(lhs.c_str(), rhs) == 0;
}
bool operator!=(const String& lhs, const char* rhs) {
	return strcmp(lhs.c_str(), rhs) != 0;
}

String::String(String&& otherString)
{
	str_ = otherString.str_;
	size_ = otherString.size_;
	otherString.str_ = nullptr;
}

String& String::operator=(String&& otherString)
{
	if (this != &otherString)
	{
		free();
		str_ = otherString.str_;
		otherString.str_ = nullptr;
		size_ = otherString.size_;
	}
	return *this;
}