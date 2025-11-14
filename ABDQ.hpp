#pragma once

#include "Interfaces.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* array_;               // underlying dynamic array
    std::size_t capacity_;   // total allocated capacity
    std::size_t curr_size_;  // number of stored elements
    std::size_t front_;      // index of front element
    std::size_t back_;       // index after the last element (circular)
    static constexpr std::size_t SCALE_FACTOR = 2;

    void ensureCapacity() {
        if (curr_size_ < capacity_) return;

        std::size_t newCapacity = capacity_ * SCALE_FACTOR;
        T* newArray = new T[newCapacity];

        for (std::size_t i = 0; i < curr_size_; ++i)
            newArray[i] = array_[(front_ + i) % capacity_];

        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = curr_size_;
    }

public:
    // Constructors
    ABDQ() : array_(new T[1]), capacity_(1), curr_size_(0), front_(0), back_(0) {}

    explicit ABDQ(std::size_t cap)
        : array_(new T[cap]), capacity_(cap), curr_size_(0), front_(0), back_(0) {}

    ABDQ(const ABDQ& other)
        : array_(new T[other.capacity_]), capacity_(other.capacity_),
          curr_size_(other.curr_size_), front_(0), back_(other.curr_size_) {
        for (std::size_t i = 0; i < curr_size_; ++i)
            array_[i] = other.array_[(other.front_ + i) % other.capacity_];
    }

    ABDQ& operator=(const ABDQ& rhs) {
        if (this != &rhs) {
            delete[] array_;
            capacity_ = rhs.capacity_;
            curr_size_ = rhs.curr_size_;
            front_ = 0;
            back_ = curr_size_;
            array_ = new T[capacity_];
            for (std::size_t i = 0; i < curr_size_; ++i)
                array_[i] = rhs.array_[(rhs.front_ + i) % rhs.capacity_];
        }
        return *this;
    }

    ABDQ(ABDQ&& other) noexcept
        : array_(other.array_), capacity_(other.capacity_), curr_size_(other.curr_size_),
          front_(other.front_), back_(other.back_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(ABDQ&& rhs) noexcept {
        if (this != &rhs) {
            delete[] array_;
            array_ = rhs.array_;
            capacity_ = rhs.capacity_;
            curr_size_ = rhs.curr_size_;
            front_ = rhs.front_;
            back_ = rhs.back_;

            rhs.array_ = nullptr;
            rhs.capacity_ = 0;
            rhs.curr_size_ = 0;
            rhs.front_ = 0;
            rhs.back_ = 0;
        }
        return *this;
    }

    ~ABDQ() { delete[] array_; }

    void pushBack(const T& item) override {
        ensureCapacity();
        array_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++curr_size_;
    }

    void pushFront(const T& item) override {
        ensureCapacity();
        front_ = (front_ == 0 ? capacity_ - 1 : front_ - 1);
        array_[front_] = item;
        ++curr_size_;
    }

    T popBack() override {
        if (curr_size_ == 0)
            throw std::runtime_error("Deque is empty");

        back_ = (back_ == 0 ? capacity_ - 1 : back_ - 1);
        T value = array_[back_];
        --curr_size_;
        return value;
    }

    T popFront() override {
        if (curr_size_ == 0)
            throw std::runtime_error("Deque is empty");

        T value = array_[front_];
        front_ = (front_ + 1) % capacity_;
        --curr_size_;
        return value;
    }

    const T& front() const override {
        if (curr_size_ == 0)
            throw std::runtime_error("Deque is empty");
        return array_[front_];
    }

    const T& back() const override {
        if (curr_size_ == 0)
            throw std::runtime_error("Deque is empty");
        std::size_t backIndex = (back_ == 0 ? capacity_ - 1 : back_ - 1);
        return array_[backIndex];
    }

    std::size_t getSize() const noexcept override { return curr_size_; }
};
