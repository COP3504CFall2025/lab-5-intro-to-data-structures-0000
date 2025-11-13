#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity(1), curr_size(0), array(new T[capacity]) {}

	explicit ABS(const size_t capacity) {
	this->array = new T[capacity];
	this->capacity = capacity;
	curr_size = 0;
}
    ABS(const ABS& other) {
        array = new T[other.capacity];
		std::copy(other.array, other.array + other.curr_size, array);
        capacity_ = other.capacity;
        curr_size_ = other.curr_size;
    }

    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) { return *this; }
        T* newArr = new T[rhs.capacity];
        size_t newCap = rhs.capacity;
        size_t newSize = rhs.curr_size;

        delete[] array;

        array = newArr;
        capacity = newCap;
        curr_size = newSize;

        return *this;
    }


    ABS(ABS&& other) noexcept {
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


    ABS& operator=(ABS&& rhs) noexcept {
		if (this != &rhs) { return *this; }
			T* newArr = rhs.array;
			size_t newCapacity = rhs.capacity;
			size_t newSize = rhs.curr_size;
		}

		delete[] array;

		array = newArr;
		capacity = newCapacity;
		curr_size = newSize;

		rhs.array = nullptr;
		rhs.capacity = 0;
		rhs.curr_size = 0;

		return *this;
}

    ~ABS() noexcept override {
		delete[] array;
		curr_size = 0;
		capacity = 0;
}

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override { return curr_size; }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity; }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept { return array; }

    // Push item onto the stack
    void push(const T& data) override {
		if (curr_size >= capacity) {
			T* newArr = new T[capacity * scale_factor];
			std::copy(array, array + capacity, newArr);
			delete[] array;
			array = newArr;
			capacity *= scale_factor;
		}
	curr_size++;
	array[curr_size - 1] = data;
	}

    T peek() const override {
		if (curr_size == 0) {
			throw std::out_of_range("Current array is empty");
		}
	return array[curr_size - 1];
	}

    T pop() override {
        if (curr_size == 0) {
			throw std::runtime_error("Current array is empty");
			return array[curr_size - 1];
	}


        T value = array[curr_size - 1];
        curr_size_--;

        if (curr_size < capacity / 2) {
            T* newArr = new T[capacity / scale_factor];
            std::copy(array, array + curr_size, newArr);
            delete[] array;
            array = newArr;
            capacity /= scale_factor;
        }

        return value;
    }

private:
    size_t capacity;
    size_t curr_size;
    T* array;
    static constexpr size_t scale_factor = 2;
};
