/* copied from https://github.com/Yagorundy/SVG/blob/master/src/utils/vector.hpp */

#pragma once

#include<iostream>

const size_t DEFAULT_CAPACITY = 4;

template <typename T>
class Vector {
private:
	T* data_;
	size_t size_;
	size_t capacity_;
public:
	Vector();
	Vector(const Vector<T>&);
	Vector(Vector<T>&&);
	Vector<T>& operator=(const Vector<T>&);
	Vector<T>& operator=(Vector<T>&&);
	~Vector();

	size_t getSize() const;
	size_t getCapacity() const;

	void pushBack(const T&);
	void pushBack(T&& n);
	void pushAt(const T&, const size_t);
	void pushAt(T&&, const size_t);
	T& popBack();
	T& popFront();
	T& popAt(const size_t);
	T& operator[](const size_t);
	const T& operator[](const size_t) const;
	bool empty() const;
	void clear();
	void swap(const Vector<T>&);
private:
	void copy(const Vector&);
	void free();
	void move(Vector&&);

	size_t calculateCapacity(const size_t) const;
	void resize(const size_t);
};

template <typename T>
Vector<T>::Vector() {
	data_ = nullptr;
	capacity_ = size_ = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
	copy(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) {
	move(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other)
	{
		free();
		move(std::move(other));
	}

	return *this;
}

template <typename T>
Vector<T>::~Vector() {
	free();
}

template <typename T>
size_t Vector<T>::getSize() const {
	return size_;
}

template <typename T>
size_t Vector<T>::getCapacity() const {
	return capacity_;
}

template <typename T>
void Vector<T>::pushBack(const T& element) {
	if (size_ + 1 > capacity_)
		resize(size_ + 1);

	data_[size_++] = element;
}


template <typename T>
void Vector<T>::pushBack(T&& element) {
	if (size_ + 1 > capacity_)
		resize(size_ + 1);

	data_[size_++] = element;
}

template <typename T>
void Vector<T>::pushAt(const T& element, const size_t index) {
	if (size_ + 1 > capacity_)
		resize(size_ + 1);

	for (size_t i = size_; i > index; i--)
		data_[i] = data_[i - 1];

	data_[index] = element;
	size_++;
}

template <typename T>
void Vector<T>::pushAt(T&& element, const size_t index) {
	if (size_ + 1 > capacity_)
		resize(size_ + 1);

	for (size_t i = size_; i > index; i--)
		data_[i] = data_[i - 1];

	data_[index] = element;
	size_++;
}

template <typename T>
T& Vector<T>::popBack() {
	if (empty())
		throw "Vector is empty";

	return data_[--size_];
}

template <typename T>
T& Vector<T>::popFront() {
	return popAt(0);
}

template <typename T>
T& Vector<T>::popAt(size_t index) {
	if (index < 0 || index >= size_)
		throw "Invalid index";

	T temp = data_[index];
	for (size_t i = index; i < size_ - 1; i++)
		data_[i] = data_[i + 1];

	size_--;
	return temp;
}

template <typename T>
T& Vector<T>::operator[](const size_t index) {
	if (index < 0 || index >= size_)
		throw "Invalid index";

	return data_[index];
}

template <typename T>
const T& Vector<T>::operator[](const size_t index) const {
	if (index < 0 || index >= size_)
		throw "Invalid index";

	return data_[index];
}

template <typename T>
bool Vector<T>::empty() const {
	return size_ == 0;
}

template <typename T>
void Vector<T>::clear() {
	delete[] data_;
	capacity_ = DEFAULT_CAPACITY;
	data_ = new T[capacity_];
	size_ = 0;
}

template <typename T>
void Vector<T>::swap(const Vector<T>& other) {
	Vector<T> tempVector(std::move(*this));
	*this = std::move(other);
	other = std::move(tempVector);
}

template <typename T>
void Vector<T>::copy(const Vector<T>& other) {
	size_ = other.size_;
	capacity_ = other.capacity_;
	data_ = new T[capacity_];

	for (size_t i = 0; i < size_; i++)
		data_[i] = other[i];
}

template <typename T>
void Vector<T>::free() {
	delete[] data_;
	data_ = nullptr;
	capacity_ = size_ = 0;
}

template <typename T>
void Vector<T>::move(Vector&& other)
{
	data_ = other.data_;
	size_ = other.size_;
	capacity_ = other.capacity_;

	other.data_ = nullptr;
	other.capacity_ = other.size_ = 0;
}
template <typename T>
size_t Vector<T>::calculateCapacity(const size_t number) const {
	size_t result = DEFAULT_CAPACITY;
	while (number > result)
		result *= 2;

	return result;
}

template <typename T>
void Vector<T>::resize(const size_t expectedCapacityToFit) {
	capacity_ = calculateCapacity(expectedCapacityToFit);
	T* temp = new T[capacity_];

	for (size_t i = 0; i < size_; i++)
		temp[i] = data_[i];

	delete[] data_;
	data_ = temp;
}