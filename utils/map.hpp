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
		Vector<MapEntry<K, V>> entries_;

		int indexOf(const K& key) const {
			int l = 0, r = entries_.getSize() - 1;
			while (l <= r) {
				int m = l + (r - l) / 2;

				if (entries_[m].key == key)
					return m;

				if (entries_[m].key < key)
					l = m + 1;
				else
					r = m - 1;
			}
			return -1;
		}

		int upperBound(const K& key) const {
			int m, l = 0, r = entries_.getSize();

			while (l < r) {
				m = l + (r - l) / 2;
				if (key >= entries_[m].key) {
					l = m + 1;
				}
				else {
					r = m;
				}
			}
			if (l < entries_.getSize() && entries_[l].key <= key) {
				l++;
			}
			return l;
		}

	public:
		Map() { }

		const Vector<MapEntry<K, V>>& getEntries() const {
			return entries_;
		}

		bool contains(const K& key) const {
			return indexOf(key) != -1;
		}

		void set(const K& key, const V& value) {
			if (contains(key)) {
				(*this)[key] = value;
			}
			else {
				int index = upperBound(key);
				entries_.pushAt(MapEntry<K, V>(key, value), index);
			}
		}

		void remove(const K& key) {
			int index = indexOf(key);
			if (index != -1) {
				entries_.popAt(index);
			}
		}

		const V& operator[](const K& key) const {
			int index = indexOf(key);
			if (index == -1)
				throw ValidationException("Key not found");
			return entries_[index].value;
		}

		V& operator[](const K& key) {
			int index = indexOf(key);
			if (index == -1) {
				index = upperBound(key);
				entries_.pushAt(MapEntry<K, V>(key, V()), index);
			}
			return entries_[index].value;
		}
	};
}

