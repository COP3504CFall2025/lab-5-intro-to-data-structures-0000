#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity;
    size_t curr_size;
    T* array;
    static constexpr size_t scale_factor = 2;

public:
    // Constructors + Big 5
    ABQ() : capacity(1), curr_size(0), array(new T[capacity]) {}
    explicit ABQ(const size_t capacity) {
        array = new T[capacity];
        capacity = capacity;
        curr_size = 0;
    }

    ABQ(const ABQ& other) {
        array = new T[other.capacity];
        std::copy(other.array, other.array + other.curr_size, array);
        capacity = other.capacity;
        curr_size = other.curr_size;
    }

    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) { return *this; }

        T* newArr = new T[rhs.capacity];
        std::copy(rhs.array, rhs.array + rhs.curr_size, newArr);

        delete[] array;

        array = newArr;
        capacity = newCap;
        curr_size = newSize;

        return *this;
    }

    ABQ(ABQ&& other) noexcept {
        T* newArr = other.array;
        size_t newCap = other.capacity;
        size_t newSize = other.curr_size;

        array = newArr;
        capacity = newCap;
        curr_size = newSize;

        other.array = nullptr;
        other.capacity = 0;
        other.curr_size = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) { return *this; }

        T* newArr = rhs.array;
        size_t newCap = rhs.capacity;
        size_t newSize = rhs.curr_size;

        delete[] array;

        array = newArr;
        capacity = newCap;
        curr_size = newSize;

        rhs.array = nullptr;
        rhs.capacity = 0;
        rhs.curr_size = 0;

        return *this;
    }

    ~ABQ() noexcept {
        delete[] array;
        curr_size = 0;
        capacity = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override { return curr_size; }
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity; }
    [[nodiscard]] T* getData() const noexcept { return array; }

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size >= capacity) {
            T* newArr = new T[capacity * scale_factor];
            std::copy(array, array+ curr_size, newArr);
            delete[] array;
            array = newArr;
            capacity *= scale_factor;
        }

        curr_size++;
        array[curr_size - 1] = data;
    }

    // Access
    T peek() const override {
        if (curr_size == 0) {
			throw std::runtime_error("Current array is empty");
		}
        return array[0]; 
    }

    // Deletion
    T dequeue() override {
        if (curr_size == 0) {
			throw std::runtime_error("Current array is empty");
		}

        T front = array[0];

        for (size_t i = 0; i < curr_size - 1; ++i) {
            array[i] = array[i + 1];
        }

        curr_size--;

        if (curr_size < capacity/2) { 
            T* newArr = new T[capacity/scale_factor];
            std::copy(array, array+curr_size, newArr);
            delete[] array;
            array = newArr;
            capacity /= scale_factor;
        }

        return front;
    }

};
