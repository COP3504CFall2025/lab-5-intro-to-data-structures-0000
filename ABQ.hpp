#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T> {
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    size_t front_;
    size_t back_;
    static constexpr size_t scale_factor_ = 2;

    void ensureCapacity() {
        if (curr_size_ < capacity_) return;

        size_t newCapacity = capacity_ * scale_factor_;
        T* newArray = new T[newCapacity];

        for (size_t i = 0; i < curr_size_; ++i)
            newArray[i] = array_[(front_ + i) % capacity_];

        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = curr_size_;
    }

    void shrinkIfNeeded() {
    if (curr_size_ < capacity_ / 2 && capacity_ > 1) {
        std::size_t newCapacity = capacity_ / 2;
        T* newArray = new T[newCapacity];

        for (std::size_t i = 0; i < curr_size_; ++i)
            newArray[i] = array_[(front_ + i) % capacity_];

        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = curr_size_;
    }
}


public:
    ABQ() {
        capacity_ = 1;
        array_ = new T[capacity_];
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    explicit ABQ(const size_t capacity) {
        array_ = new T[capacity];
        capacity_ = capacity;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    ABQ(const ABQ& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        front_ = 0;
        back_ = curr_size_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; ++i)
            array_[i] = other.array_[(other.front_ + i) % other.capacity_];
    }

    ABQ& operator=(const ABQ& rhs) {
        if (this != &rhs) {
            delete[] array_;
            capacity_ = rhs.capacity_;
            curr_size_ = rhs.curr_size_;
            front_ = 0;
            back_ = curr_size_;
            array_ = new T[capacity_];
            for (size_t i = 0; i < curr_size_; ++i)
                array_[i] = rhs.array_[(rhs.front_ + i) % rhs.capacity_];
        }
        return *this;
    }

    ABQ(ABQ&& other) noexcept
        : capacity_(other.capacity_), curr_size_(other.curr_size_),
          array_(other.array_), front_(other.front_), back_(other.back_) {
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this != &rhs) {
            delete[] array_;
            capacity_ = rhs.capacity_;
            curr_size_ = rhs.curr_size_;
            front_ = rhs.front_;
            back_ = rhs.back_;
            array_ = rhs.array_;

            rhs.array_ = nullptr;
            rhs.curr_size_ = 0;
            rhs.capacity_ = 0;
            rhs.front_ = 0;
            rhs.back_ = 0;
        }
        return *this;
    }

    ~ABQ() noexcept override {
        delete[] array_;
    }

    [[nodiscard]] size_t getSize() const noexcept override { return curr_size_; }

    [[nodiscard]] size_t getMaxCapacity() const noexcept { return capacity_; }

    [[nodiscard]] T* getData() const noexcept { return array_; }

    void enqueue(const T& data) override {
        ensureCapacity();
        array_[back_] = data;
        back_ = (back_ + 1) % capacity_;
        ++curr_size_;
    }

    const T& peek() const override {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        return array_[front_];
    }

    T dequeue() override {
        if (curr_size_ == 0) throw std::runtime_error("Queue is empty");
        T value = array_[front_];
        front_ = (front_ + 1) % capacity_;
        --curr_size_;
        return value;
    }
};
