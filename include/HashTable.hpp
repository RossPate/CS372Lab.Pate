#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cstddef>
#include <functional>
#include <string> // Added for std::string, good practice if RecordType uses it

// Forward declaration of HashTableTest, needed for the friend declaration
// This is important because HashTableTest is not a template class itself.
class HashTableTest;

template <class RecordType>
class HashTable {
public:
    static const std::size_t CAPACITY = 811;
    static const int NEVERUSED = -1;
    static const int PREVIOUSLYUSED = -2;

    HashTable() : used(0) {}

    void insert(const RecordType& entry);
    void remove(int key);
    bool isPresent(int key) const;

    void find(int key, bool& found, RecordType& result,
        std::function<void(int, bool&, std::size_t)> hashingFunction =
        [this](int key, bool& found, std::size_t& index) {
            this->findIndex(key, found, index);
        }) const;

    std::size_t size() const { return used; }

    void findIndex(int key, bool& found, std::size_t& i) const;
    void quadraticProbe(int key, bool& found, std::size_t& i) const;
    void secondHash(int key, bool& found, std::size_t& i) const;
    const RecordType* getRawData() const { return data; } // added getter for testing purposes

protected: //Changed to protected to access in test script
    RecordType data[CAPACITY];
    std::size_t used;

    std::size_t hash(int key) const { return key % CAPACITY; }
    std::size_t nextIndex(std::size_t index) const { return (index + 1) % CAPACITY; }

    bool neverUsed(std::size_t index) const { return data[index].key == NEVERUSED; }
    bool isVacant(std::size_t index) const {
        return data[index].key == NEVERUSED || data[index].key == PREVIOUSLYUSED;
    }

    // IMPORTANT: This is the correct friend declaration for a non-template class
    // (HashTableTest) to access members of a template class (HashTable).
    // It declares HashTableTest as a friend of ALL instantiations of HashTable.
    friend class HashTableTest;
};

// ---------------------------- Implementation ----------------------------

template <class RecordType>
void HashTable<RecordType>::insert(const RecordType& entry) {
    bool alreadyPresent;
    RecordType temp;
    find(entry.key, alreadyPresent, temp);
    std::size_t index = hash(entry.key);

    if (!alreadyPresent) {
        while (!isVacant(index)) {
            index = nextIndex(index);
        }
        ++used;
    }

    data[index] = entry;
}

template <class RecordType>
void HashTable<RecordType>::remove(int key) {
    bool found;
    std::size_t index;
    findIndex(key, found, index);
    if (found) {
        data[index].key = PREVIOUSLYUSED;
        --used;
    }
}

template <class RecordType>
bool HashTable<RecordType>::isPresent(int key) const {
    bool found;
    RecordType dummy;
    find(key, found, dummy);
    return found;
}

template <class RecordType>
void HashTable<RecordType>::find(int key, bool& found, RecordType& result,
    std::function<void(int, bool&, std::size_t)> hashingFunction) const {
    std::size_t index;
    hashingFunction(key, found, index);
    if (found) {
        result = data[index];
    }
}

template <class RecordType>
void HashTable<RecordType>::findIndex(int key, bool& found, std::size_t& index) const {
    std::size_t count = 0;
    index = hash(key);
    while (count < CAPACITY && !neverUsed(index) && data[index].key != key) {
        ++count;
        index = nextIndex(index);
    }
    found = (data[index].key == key);
}

template <class RecordType>
void HashTable<RecordType>::quadraticProbe(int key, bool& found, std::size_t& i) const {
    std::size_t hashIndex = hash(key);
    std::size_t j = 0;
    i = hashIndex;
    while (j < CAPACITY && !neverUsed(i) && data[i].key != key) {
        ++j;
        i = (hashIndex + j * j) % CAPACITY;
    }
    found = (data[i].key == key);
}

template <class RecordType>
void HashTable<RecordType>::secondHash(int key, bool& found, std::size_t& i) const {
    std::size_t hash1 = hash(key);
    std::size_t hash2 = 7 - (key % 7);
    std::size_t j = 0;
    i = hash1;
    while (j < CAPACITY && !neverUsed(i) && data[i].key != key) {
        ++j;
        i = (hash1 + j * hash2) % CAPACITY;
    }
    found = (data[i].key == key);
}

#endif // HASHTABLE_HPP
