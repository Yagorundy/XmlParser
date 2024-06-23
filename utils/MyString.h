/* initially copied from https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2010/String%20and%20StringView/MyString.h */

#pragma once
#include <iostream>

class MyString
{
public:
    MyString();
    MyString(const char* data);

    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;

    MyString& operator=(const MyString& other);

    MyString& operator=(MyString&& other) noexcept;
    ~MyString();

    size_t getCapacity() const;
    size_t getSize() const;

    const char* c_str() const;

    MyString& operator+=(const MyString& other);

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
    friend std::istream& operator>>(std::istream& is, MyString& ref);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);

    MyString substr(size_t begin, size_t howMany) const;

    // additions
    MyString& operator +=(const char* other);
    void getLine(std::istream& out);
    MyString substr(size_t begin) const;
    size_t find(char ch, size_t pos) const;
    MyString& operator +=(const char& ch);
    bool empty() const;
    MyString trim() const;

private:
    explicit MyString(size_t stringLength);
    void resize(unsigned newAllocatedDataSize);

    void free();
    void copyFrom(const MyString& other);

    void moveFrom(MyString&& other);

    char* _data;
    size_t _size;
    size_t _allocatedDataSize;
};



bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);