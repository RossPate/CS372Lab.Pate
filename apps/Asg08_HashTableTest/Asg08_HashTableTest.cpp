// I used a lot of AI to try and help me figure the testing situation out on this one.
// Still no good luck and eventually I think I would need to rewrite everything.
#include "gtest/gtest.h"
#include "HashTable.hpp"
#include <string>

// Define a simple RecordType for testing
struct TestRecord {
    int key;
    std::string value;

    TestRecord() : key(HashTable<TestRecord>::NEVERUSED), value("") {}
    TestRecord(int k, const std::string& v) : key(k), value(v) {}

    bool operator==(const TestRecord& other) const {
        return key == other.key && value == other.value;
    }
};

// Define a test fixture
class HashTableTest : public ::testing::Test {
protected:
    HashTable<TestRecord> table;
};

// -------------------------- Tests --------------------------

TEST_F(HashTableTest, DefaultConstructor) {
    EXPECT_EQ(table.size(), 0);
    const TestRecord* raw = table.getRawData();
    for (std::size_t i = 0; i < HashTable<TestRecord>::CAPACITY; ++i) {
        EXPECT_EQ(raw[i].key, HashTable<TestRecord>::NEVERUSED);
    }
}

TEST_F(HashTableTest, InsertSingleElement) {
    table.insert(TestRecord(10, "Apple"));
    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.isPresent(10));

    bool found = false;
    TestRecord foundRecord;
    table.find(10, found, foundRecord);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundRecord.value, "Apple");
}

TEST_F(HashTableTest, InsertMultipleElements) {
    table.insert(TestRecord(10, "Apple"));
    table.insert(TestRecord(20, "Banana"));
    table.insert(TestRecord(30, "Cherry"));

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.isPresent(10));
    EXPECT_TRUE(table.isPresent(20));
    EXPECT_TRUE(table.isPresent(30));
}

TEST_F(HashTableTest, InsertDuplicateKey) {
    table.insert(TestRecord(10, "Apple"));
    table.insert(TestRecord(10, "Orange")); // Overwrite
    EXPECT_EQ(table.size(), 1);

    bool found = false;
    TestRecord foundRecord;
    table.find(10, found, foundRecord);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundRecord.value, "Orange");
}

TEST_F(HashTableTest, RemoveExistingElement) {
    table.insert(TestRecord(10, "Apple"));
    table.insert(TestRecord(20, "Banana"));
    EXPECT_EQ(table.size(), 2);

    table.remove(10);
    EXPECT_EQ(table.size(), 1);
    EXPECT_FALSE(table.isPresent(10));
    EXPECT_TRUE(table.isPresent(20));

    std::size_t index;
    bool found = false;
    table.findIndex(10, found, index);
    EXPECT_FALSE(found);

    const TestRecord* raw = table.getRawData();
    EXPECT_EQ(raw[index].key, HashTable<TestRecord>::PREVIOUSLYUSED);
}

TEST_F(HashTableTest, RemoveNonExistingElement) {
    table.insert(TestRecord(10, "Apple"));
    table.remove(99);
    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.isPresent(10));
}

TEST_F(HashTableTest, IsPresent) {
    EXPECT_FALSE(table.isPresent(100));
    table.insert(TestRecord(100, "Test"));
    EXPECT_TRUE(table.isPresent(100));
    table.remove(100);
    EXPECT_FALSE(table.isPresent(100));
}

TEST_F(HashTableTest, FindWithDefaultHashing) {
    table.insert(TestRecord(10, "One"));
    table.insert(TestRecord(20, "Two"));

    bool found = false;
    TestRecord result;

    table.find(10, found, result);
    EXPECT_TRUE(found);
    EXPECT_EQ(result.value, "One");

    table.find(20, found, result);
    EXPECT_TRUE(found);
    EXPECT_EQ(result.value, "Two");

    table.find(99, found, result);
    EXPECT_FALSE(found);
}

TEST_F(HashTableTest, LinearProbingCollision) {
    table.insert(TestRecord(10, "First"));
    table.insert(TestRecord(821, "Second")); // Collides with 10

    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.isPresent(10));
    EXPECT_TRUE(table.isPresent(821));

    bool found = false;
    TestRecord foundRecord;

    table.find(10, found, foundRecord);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundRecord.value, "First");

    table.find(821, found, foundRecord);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundRecord.value, "Second");

    table.remove(10);
    EXPECT_EQ(table.size(), 1);
    EXPECT_FALSE(table.isPresent(10));
    EXPECT_TRUE(table.isPresent(821));
}

TEST_F(HashTableTest, FindWithQuadraticProbing) {
    table.insert(TestRecord(10, "Original"));
    table.insert(TestRecord(821, "Quadratic"));

    auto quadraticProbe = [&table = this->table](int key, bool& found, std::size_t& idx) {
        table.quadraticProbe(key, found, idx);
        };

    bool found = false;
    TestRecord result;

    table.find(10, found, result, quadraticProbe);
    EXPECT_TRUE(found);
    EXPECT_EQ(result.value, "Original");

    table.find(821, found, result, quadraticProbe);
    EXPECT_TRUE(found);
    EXPECT_EQ(result.value, "Quadratic");

    table.find(999, found, result, quadraticProbe);
    EXPECT_FALSE(found);
}

TEST_F(HashTableTest, FindWithSecondHashing) {
    table.insert(TestRecord(10, "FirstHash"));
    table.insert(TestRecord(821, "SecondHash"));

    auto secondHash = [&table = this->table](int key, bool& found, std::size_t& idx) {
        table.secondHash(key, found, idx);
        };

    bool found = false;
    TestRecord result;

    table.find(10, found, result, secondHash);
    EXPECT_TRUE(found);
    EXPECT_EQ(result.value, "FirstHash");

    table.find(821, found, result, secondHash);
    EXPECT_TRUE(found);
    EXPECT_EQ(result.value, "SecondHash");

    table.find(999, found, result, secondHash);
    EXPECT_FALSE(found);
}

TEST_F(HashTableTest, InsertAfterRemoval) {
    table.insert(TestRecord(10, "Original"));
    table.insert(TestRecord(821, "Collision"));
    table.remove(10);
    EXPECT_EQ(table.size(), 1);

    table.insert(TestRecord(10, "NewValue"));
    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.isPresent(10));

    bool found = false;
    TestRecord foundRecord;
    table.find(10, found, foundRecord);
    EXPECT_TRUE(found);
    EXPECT_EQ(foundRecord.value, "NewValue");
}

TEST_F(HashTableTest, ManyInsertions) {
    const int NUM_ELEMENTS = 500;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        table.insert(TestRecord(i, "Val_" + std::to_string(i)));
    }

    EXPECT_EQ(table.size(), NUM_ELEMENTS);

    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        EXPECT_TRUE(table.isPresent(i));
        bool found = false;
        TestRecord r;
        table.find(i, found, r);
        EXPECT_TRUE(found);
        EXPECT_EQ(r.value, "Val_" + std::to_string(i));
    }

    EXPECT_FALSE(table.isPresent(NUM_ELEMENTS + 1));
}

TEST_F(HashTableTest, ManyInsertionsAndRemovals) {
    const int NUM = 500;
    for (int i = 0; i < NUM; ++i) {
        table.insert(TestRecord(i, "Val_" + std::to_string(i)));
    }
    EXPECT_EQ(table.size(), NUM);

    for (int i = 0; i < NUM / 2; ++i) {
        table.remove(i);
    }

    EXPECT_EQ(table.size(), NUM / 2);

    for (int i = 0; i < NUM / 2; ++i) {
        EXPECT_FALSE(table.isPresent(i));
    }
    for (int i = NUM / 2; i < NUM; ++i) {
        EXPECT_TRUE(table.isPresent(i));
    }

    for (int i = NUM; i < NUM + 100; ++i) {
        table.insert(TestRecord(i, "New_" + std::to_string(i)));
    }

    EXPECT_EQ(table.size(), NUM / 2 + 100);

    for (int i = NUM; i < NUM + 100; ++i) {
        EXPECT_TRUE(table.isPresent(i));
    }
}

// -------------------------- Main --------------------------

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
