//
// File: Assignment02.cpp
// Author: Ross Pate - rpate@my.athens.edu
// Purpose: Vector deep copy versus std::copy comparisons
//

// Author's note: I'm sorry for the frequent use of this->, I prefer more readable code but I kept running in to -
// an error where vCapacity was an undeclared identifier despite it being protected and useable in the derived classes. (probably a c++ version error on my part).
#include <iostream>
#include <chrono>
#include <algorithm>

template <typename T>
class Vector {
public:
    Vector() {
        arr = new T[vCapacity];
    }

    virtual ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

    virtual void expand(int newCapacity) {
        if (newCapacity > vCapacity) {
            T* temp = new T[newCapacity];
            for (int i = 0; i < length; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            vCapacity = newCapacity;
        }
        else {
            std::cerr << "Vector::expand: new capacity must be greater than current" << std::endl;
        }
    }

    void push_back(T data) {
        if (length == vCapacity) {
            expand(2 * vCapacity);
        }
        arr[length++] = data;
    }

    int size() { return length; }
    int capacity() { return vCapacity; }

protected:  // Allow subclasses to access these members
    T* arr;
    int vCapacity = 1;
    int length = 0;
};

// Subclass using STL copy algorithm for resizing
template <typename T>
class VectorSTL : public Vector<T> {
public:
    void expand(int newCapacity) override {
        if (newCapacity > this->vCapacity) {
            T* temp = new T[newCapacity];
            std::copy(this->arr, this->arr + this->length, temp);
            delete[] this->arr;
            this->arr = temp;
            this->vCapacity = newCapacity; 
        }
        else {
            std::cerr << "VectorSTL::expand: new capacity must be greater than current" << std::endl;
        }
    }
};

// Subclass with larger initial capacity and 4x expansion
template <typename T>
class VectorLargeStep : public Vector<T> {
public:
    VectorLargeStep() {
        this->vCapacity = 128; 
        this->arr = new T[this->vCapacity];
    }

    void expand(int newCapacity) override {
        if (newCapacity > this->vCapacity) { 
            T* temp = new T[newCapacity];
            std::copy(this->arr, this->arr + this->length, temp);
            delete[] this->arr;
            this->arr = temp;
            this->vCapacity = newCapacity;
        }
        else {
            std::cerr << "VectorLargeStep::expand: new capacity must be greater than current" << std::endl;
        }
    }

    void push_back(T data) {
        if (this->length == this->vCapacity) {
            expand(this->vCapacity * 4);  // Increase size by 4x instead of 2x
        }
        this->arr[this->length++] = data;
    }
};

template <typename VecType>
void testPerformance(const std::string& name) {
    VecType vec;
    std::cout << name << ":\nSize\tTime (ms)" << std::endl;

    double totalTime = 0.0;  // Variable to store total time

    for (int n = 2; n <= 4096; n *= 2) {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < n; i++) {
            vec.push_back(i);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        totalTime += elapsed.count();  // Add each individual measurement to total

        std::cout << n << "\t" << elapsed.count() << " ms" << std::endl;
    }

    // Display the total time taken by this method
    std::cout << "Total time for " << name << ": " << totalTime << " ms\n" << std::endl;
}

int main() {
    testPerformance<Vector<int>>("Base Vector (Deep Copy)");
    testPerformance<VectorSTL<int>>("VectorSTL (std::copy)");
    testPerformance<VectorLargeStep<int>>("VectorLargeStep (Start at 128, Increase by 4x)");

    return 0;
}