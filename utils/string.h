/* copied from https://github.com/Yagorundy/SVG/blob/master/src/utils/string.h */

#pragma once

#include <fstream>
#include <iostream>

#include "vector.hpp"

class String
{
	char* str_;
	size_t size_;

	void copyFrom(const String& other);
	void free();

public:
	String();
	String(const char*);

	String(const String&);

	String(String&&); //move constructor that accepts rvalue;

	String& operator=(const String& other);
	String& operator=(String&& other);  //move op= that accepts rvalue;

	~String();

	size_t getSize() const;
	void concat(const String& other);

	char& operator[](const size_t);
	const char& operator[](const size_t) const;

	const char* c_str() const;

	String& operator+=(const String& other);

	friend std::ostream& operator<<(std::ostream& stream, const String& str);
	friend std::istream& operator>>(std::istream& stream, String& str);
	void getLine(std::istream& out);

	String trim() const;
	String substring(int start) const;
	String substring(int start, int end) const;

	Vector<String> split(const char& delim) const;
};

String operator+(const String& lhs, const String& rhs);

bool operator==(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);

bool operator==(const String& lhs, const char* rhs);
bool operator!=(const String& lhs, const char* rhs);