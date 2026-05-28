#include "HashTable.h"
#include <cmath>
#include <stdexcept>

HashTable::HashTable(size_t size) noexcept
    : _capacity(static_cast<int32_t>(size)),
      _filled(0),
      table(_capacity)
{
}

HashTable::~HashTable() = default;

size_t HashTable::hash_div(const KeyType &key) const {
    size_t hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + static_cast<size_t>(ch)) % _capacity;
    }
    return hash;
}

size_t HashTable::hash_mul(const KeyType &key) const {
    const double A = 0.6180339887498949;
    size_t hash = 0;
    for (char ch : key) {
        hash = hash * 31 + static_cast<size_t>(ch);
    }
    double fractional = hash * A - floor(hash * A);
    return static_cast<size_t>(_capacity * fractional);
}
size_t HashTable::hash_function(const KeyType &key) const {
    return hash_div(key);
    // return hash_mul(key);
}

double HashTable::getLoadFactor() {
    return static_cast<double>(_filled) / _capacity;
}

void HashTable::rehash() {
    int32_t new_capacity = _capacity * 2;
    std::vector<std::list<std::pair<KeyType, ValueType>>> new_table(new_capacity);

    auto old_table = std::move(table);
    int32_t old_capacity = _capacity;

    _capacity = new_capacity;
    table = std::move(new_table);
    _filled = 0; 
    for (const auto &bucket : old_table) {
        for (const auto &pair : bucket) {
            insert(pair.first, pair.second);
        }
    }
}
void HashTable::insert(const KeyType &key, const ValueType &value) {
    if (getLoadFactor() > 0.75) {
        rehash();
    }
    
    size_t index = hash_function(key);
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            pair.second = value;
	    return;
        }
    }
    table[index].push_back({key, value});
    ++_filled;
}

bool HashTable::find(const KeyType &key, ValueType &value) const {
    size_t index = hash_function(key);
    for (const auto &pair : table[index]) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key) {
    size_t index = hash_function(key);
    auto &bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            --_filled;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key) {
    size_t index = hash_function(key);
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    insert(key, 0.0);
    index = hash_function(key);
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    throw std::runtime_error("HashTable operator[] failed to insert key");
}
