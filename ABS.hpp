#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    ABS() {
        array_ = new T[1];
        capacity_ = 1;
        curr_size_ = 0;
    }

    explicit ABS(const size_t capacity) {
        array_ = new T[capacity];
        capacity_ = capacity;
        curr_size_ = 0;
    }

    ABS(const ABS& other) {
        array_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        std::copy(other.array_, other.array_ + other.curr_size_, array_);
    }

    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) return *this;
        T* newArr = new T[rhs.capacity_];
        std::copy(rhs.array_, rhs.array_ + rhs.curr_size_, newArr);
        delete[] array_;
        array_ = newArr;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        return *this;
    }

    ABS(ABS&& other) noexcept {
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) return *this;
        delete[] array_;
        array_ = rhs.array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        return *this;
    }

    ~ABS() noexcept override {
        delete[] array_;
        capacity_ = 0;
        curr_size_ = 0;
    }

    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    void push(const T& data) override {
        if (curr_size_ >= capacity_) {
            T* newArr = new T[capacity_ * scale_factor_];
            std::copy(array_, array_ + curr_size_, newArr);
            delete[] array_;
            array_ = newArr;
            capacity_ *= scale_factor_;
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override {
        if (curr_size_ == 0) throw std::runtime_error("Stack is empty");
        return array_[curr_size_ - 1];
    }

    T pop() override {
        if (curr_size_ == 0) throw std::runtime_error("Stack is empty");
        curr_size_--;
        T value = array_[curr_size_];
        if (curr_size_ < capacity_ / 2) {
            T* newArr = new T[capacity_ / scale_factor_];
            std::copy(array_, array_ + curr_size_, newArr);
            delete[] array_;
            array_ = newArr;
            capacity_ = newCap;
        }

        return value;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};