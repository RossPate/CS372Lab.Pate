//
// File: FinalExam_P2.cpp
// Author: Ross Pate
// Purpose: Partioning a list then using recursive version of quicksort to sort the list
//
#include <iostream>
#include <list>
#include <iterator>

template<typename T>
void partition(const T& pivot, const std::list<T>& input,
    std::list<T>* less,
    std::list<T>* greater) {
    for (const T& item : input) {
        if (item < pivot) {
            less->push_back(item);
        }
        else if (item > pivot) {
            greater->push_back(item);
        }
    }
}

template<typename T>
std::list<T>* quicksort(const std::list<T>& input) {
    if (input.size() <= 1) {
        return new std::list<T>(input); // List is already sorted
    }

    // first element = pivot
    T pivot = input.front();

    std::list<T> less;
    std::list<T> greater;

    // Create input
    std::list<T> remaining(input);
    remaining.pop_front();  // Remove pivot 

    partition(pivot, remaining, &less, &greater);

    std::list<T>* sortedLess = quicksort(less);
    std::list<T>* sortedGreater = quicksort(greater);

    auto* result = new std::list<T>();
    result->splice(result->end(), *sortedLess);
    result->push_back(pivot);
    result->splice(result->end(), *sortedGreater);

	// sweep up memory
    delete sortedLess;
    delete sortedGreater;

    return result;
}

// Test function using chatgpt to generate random list of integers + easy "testing"
int main() {
    std::list<int> myList = { 7, 2, 1, 9, 5, 3, 8 };

    std::list<int>* sortedList = quicksort(myList);

    std::cout << "Sorted list: ";
    for (int val : *sortedList) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    delete sortedList;
    return 0;
}
