#pragma once
#include <vector>
#include <stdexcept>

template <typename Thing>
class ReceiptBag {
private:
    std::vector<Thing> items;
    std::vector<int> receipts;
    int nextReceipt;

public:
    ReceiptBag() : nextReceipt(1) {} // Start at 1

    // Inserts an item and returns a unique receipt
    int insert(Thing aThing) {
        items.push_back(aThing);
        receipts.push_back(nextReceipt);
        return nextReceipt++;
    }

    Thing remove(int receipt) {
        for (size_t i = 0; i < receipts.size(); ++i) {
            if (receipts[i] == receipt) {
                Thing removedItem = items[i];
                items.erase(items.begin() + i);
                receipts.erase(receipts.begin() + i);
                return removedItem;
            }
        }
        throw std::invalid_argument("Receipt not found");
    }

    // Returns the number of items in the bag
    int size() const {
        return items.size();
    }

    // Returns the number of receipts
    int count() const {
        return receipts.size();
    }
};