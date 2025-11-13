#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Constructors
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABS(size_t capacity) {
        array_ = new T[capacity];
        capacity_ = capacity;
        curr_size_ = 0;
    }

    ABS(const ABS& other) {
        array_ = new T[other.capacity_];

        for (size_t i = 0; i < other.curr_size_; i++) {
            array_[i] = other.array_[i];
        }

        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
    }

    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) { return *this; }
        T* newArr = rhs.array_;
        size_t newCap = rhs.capacity_;
        size_t newSize = rhs.curr_size_;

        delete[] array_;

        array_ = newArr;
        capacity_ = newCap;
        curr_size_ = newSize;

        return *this;
    }

    ABS(ABS&& other) noexcept {
        T* newArr = other.array_;
        size_t newCap = other.capacity_;
        size_t newSize = other.curr_size_;

        array_ = newArr;
        capacity_ = newCap;
        curr_size_ = newSize;

        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) { return *this; }
        T* newArr = rhs.array_;
        size_t newCap = rhs.capacity_;
        size_t newSize = rhs.curr_size_;

        delete[] array_;

        array_ = newArr;
        capacity_ = newCap;
        curr_size_ = newSize;

        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;

        return *this;
    }

    ~ABS() noexcept {
        delete[] array_;
        curr_size_ = 0;
        capacity_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept { return array_; }

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size_ >= capacity_) {
            T* newArr = new T[capacity_*scale_factor_];
            std::copy(array_, array_+ curr_size_, newArr);
            delete[] array_;
            array_ = newArr;
            capacity_ *= scale_factor_;
        }

        curr_size_++;
        array_[curr_size_-1] = data;
    }

    T peek() const override {
        if (curr_size_ == 0) { throw std::runtime_error("Current array is empty"); }
        return array_[curr_size_-1];
    }

    T pop() override {
        if (curr_size_ == 0) { throw std::runtime_error("Current array is empty"); }

        T value = array_[curr_size_-1];
        curr_size_--;

        if (curr_size_ < capacity_/2) {
            T* newArr = new T[capacity_/scale_factor_];
            std::copy(array_, array_+curr_size_, newArr);
            delete[] array_;
            array_ = newArr;
            capacity_ /= scale_factor_;
        }

        return value;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};