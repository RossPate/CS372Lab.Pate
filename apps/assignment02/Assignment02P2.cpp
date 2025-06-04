//
// File : Assignment02P2.cpp
// Author : Ross Pate - rpate@my.athens.edu
// Purpose : Array template class with STL convention and parameterized by data type and size.
//

#include <iostream>
#include <stdexcept>  // For exceptions if index = out of bounds

template <typename T, size_t N>
class Array {
public:
    Array() {
        arr = new T[N]{};
    }

    // Destructor
    ~Array() {
        delete[] arr;
    }

    // Copy Constructor
    Array(const Array& other) {
        arr = new T[N];
        for (size_t i = 0; i < N; i++) {
            arr[i] = other.arr[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            for (size_t i = 0; i < N; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    T& at(size_t index) {
        if (index >= N) {
            throw std::out_of_range("Array index out of bounds");
        }
        return arr[index];
    }

    T& operator[](size_t index) {
        return arr[index]; 
    }

    // Size Function
    size_t size() const { return N; }

    // Traverse the Array
    void traverse() const {
        for (size_t i = 0; i < N; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    T* arr;
};