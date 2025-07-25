//
// File: PateExam_P3.cpp
// Author: Ross Pate
// Purpose: Hash table implementation with quadratic probing
//
#include <cassert>
#include <cstddef>
#include <string>
#include <iostream>

template <class RecordType>
class Table {
public:
    static const std::size_t CAPACITY = 1024; // Must be a power of 2

    Table() : used(0) {
        for (std::size_t i = 0; i < CAPACITY; ++i)
            data[i].key = NEVERUSED;
    }

    void insert(const RecordType& entry) {
        bool alreadyPresent;
        std::size_t index;
        assert(entry.key >= 0);
        findIndex(entry.key, alreadyPresent, index);

        if (!alreadyPresent) {
            assert(size() < CAPACITY);
            index = hash(entry.key);

            // ✅ Optional improvement: only probe if there is a collision
            if (!isVacant(index)) {
                quadProbe(index);
            }

            ++used;
        }

        data[index] = entry;
    }

    void remove(int key) {
        bool found;
        std::size_t index;
        assert(key >= 0);
        findIndex(key, found, index);
        if (found) {
            data[index].key = PREVIOUSLYUSED;
            --used;
        }
    }

    bool isPresent(int key) const {
        bool found;
        std::size_t index;
        findIndex(key, found, index);
        return found;
    }

    void find(int key, bool& found, RecordType& result) const {
        std::size_t index;
        findIndex(key, found, index);
        if (found)
            result = data[index];
    }

    std::size_t size() const { return used; }

private:
    static const int NEVERUSED = -1;
    static const int PREVIOUSLYUSED = -2;

    RecordType data[CAPACITY];
    std::size_t used;

    std::size_t hash(int key) const {
        return static_cast<std::size_t>(key) % CAPACITY;
    }

    void quadProbe(std::size_t& index) {
        std::size_t original = index;
        std::size_t i = 1;
        while (!isVacant(index)) {
            index = (original + i * i) % CAPACITY;
            ++i;
            if (i == CAPACITY) break; // Avoid infinite loop
        }
    }

    void findIndex(int key, bool& found, std::size_t& index) const {
        std::size_t count = 0;
        std::size_t i = hash(key);
        std::size_t probeStep = 1;

        while (count < CAPACITY &&
            data[i].key != NEVERUSED &&
            data[i].key != key) {
            i = (i + probeStep * probeStep) % CAPACITY;
            ++probeStep;
            ++count;
        }

        found = (data[i].key == key);
        index = i;
    }

    bool isVacant(std::size_t index) const {
        return (data[index].key == NEVERUSED || data[index].key == PREVIOUSLYUSED);
    }
};

struct Record {
    int key;
    std::string value;
};
// Used chatgpt again to generate a main function to test the Table class
int main() {
    Table<Record> hashTable;

    Record a = { 42, "Hello" };
    Record b = { 1066, "World" };

    hashTable.insert(a);
    hashTable.insert(b);

    bool found;
    Record result;
    hashTable.find(42, found, result);
    if (found)
        std::cout << result.value << "\n"; // Should print "Hello"
}
