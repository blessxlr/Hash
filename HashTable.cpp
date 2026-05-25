#include "HashTable.h"
#include <stdexcept>
#include <cmath>

HashTable::HashTable(size_t size) noexcept
    : _capacity(static_cast<int32_t>(size)),
      _filled(0),
      table(_capacity)
{
}

HashTable::~HashTable()
{
}

size_t HashTable::hash_function(const KeyType &key) const
{
    size_t hash = 0;
    for (char c : key) {
        hash = hash * 31 + static_cast<size_t>(c);
    }
    return hash % _capacity;
}

bool HashTable::find(const KeyType &key, ValueType &value) const
{
    size_t index = hash_function(key);
    for (const auto &pair : table[index]) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    return false;
}

void HashTable::remove(const KeyType &key)
{
    size_t index = hash_function(key);
    auto &bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            _filled--;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key)
{
    size_t index = hash_function(key);
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    insert(key, 0.0);
    
    // После вставки мог произойти rehash, ищем снова
    index = hash_function(key);
    for (auto &pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }

    throw std::runtime_error("HashTable operator[] failed");
}

double HashTable::getLoadFactor()
{
    return static_cast<double>(_filled) / _capacity;
}

void HashTable::rehash()
{
    int32_t newCapacity = _capacity * 2;
    std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(newCapacity);

    for (auto &bucket : table) {
        for (auto &pair : bucket) {
            size_t hash = 0;
            for (char c : pair.first) {
                hash = hash * 31 + static_cast<size_t>(c);
            }
            size_t newIndex = hash % newCapacity;
            newTable[newIndex].push_back(pair);
        }
    }

    table = std::move(newTable);
    _capacity = newCapacity;
}

void HashTable::insert(const KeyType &key, const ValueType &value)
{
    if (static_cast<double>(_filled) / _capacity > 0.75) {
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
    _filled++;
}
