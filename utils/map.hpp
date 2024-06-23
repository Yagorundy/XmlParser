#pragma once

#include "vector.hpp"
#include "app_exceptions.h"

namespace XmlParser {
	template <typename K, typename V>
	struct MapEntry {
		K key;
		V value;

		MapEntry() : key(), value() {}
		MapEntry(const K& key, const V& value) : key(key), value(value) {}
	};

	template <typename K, typename V>
	class Map {
	private:
		Vector<MapEntry<K, V>> data_;

		int indexOf(const K& key) const {
			int l = 0, r = data_.getSize() - 1;
			while (l <= r) {
				int m = l + (r - l) / 2;

				if (data_[m].key == key)
					return m;

				if (data_[m].key < key)
					l = m + 1;
				else
					r = m - 1;
			}
			return -1;
		}

		int upperBound(const K& key) const {
			int m, l = 0, r = data_.getSize();

			while (l < r) {
				m = l + (r - l) / 2;
				if (key >= data_[m].key) {
					l = m + 1;
				}
				else {
					r = m;
				}
			}
			if (l < data_.getSize() && data_[l].key <= key) {
				l++;
			}
			return l;
		}

	public:
		Map() { }

		bool contains(const K& key) const {
			return indexOf(key) != -1;
		}

		void set(const K& key, const V& value) {
			if (contains(key)) {
				(*this)[key] = value;
			}
			else {
				int index = upperBound(key);
				data_.pushAt(MapEntry<K, V>(key, value), index);
			}
		}

		void remove(const K& key) {
			int index = indexOf(key);
			if (index != -1) {
				data_.popAt(index);
			}
		}

		const V& operator[](const K& key) const {
			int index = indexOf(key);
			if (index == -1)
				throw ValidationException("Key not found");
			return data_[index].value;
		}

		V& operator[](const K& key) {
			int index = indexOf(key);
			if (index == -1) {
				index = upperBound(key);
				data_.pushAt(MapEntry<K, V>(key, V()), index);
			}
			return data_[index].value;
		}
	};
}

