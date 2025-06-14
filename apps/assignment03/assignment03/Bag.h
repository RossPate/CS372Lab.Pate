#pragma once
#include "List.h"

template <typename Thing>
class Bag {
private:
    List<Thing> items;
public:
    Bag() = default;

    void insert(Thing aThing) {
        items.push_back(aThing);
    }

    Thing& pop() {
        if (items.empty()) {
            throw std::out_of_range("Bag is empty");
        }
        Thing& item = items.back();
        items.pop_back();
        return item;
    }

    int size() const {
        return static_cast<int>(items.size());
    }

    int count() const {
        return static_cast<int>(items.size());
    }
};