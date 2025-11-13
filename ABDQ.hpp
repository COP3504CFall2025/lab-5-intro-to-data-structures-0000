#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include "Interfaces.hpp"

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;
    std::size_t capacity_;
    std::size_t size_;
    std::size_t front_;
    std::size_t back_;

    static constexpr std::size_t SCALE_FACTOR = 2;

    void resize(std::size_t newCap) {
        if (newCap < 1) newCap = 1;

        T* newData = new T[newCap];

        for (std::size_t i = 0; i < size_; i++) {
            newData[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCap;
        front_ = 0;
        back_ = size_;
    }

    void ensureCapacity() {
        if (size_ == capacity_) {
            resize(capacity_ * SCALE_FACTOR);
        }
    }

    void shrinkIfNeeded() {
        if (capacity_ > 1 && size_ <= capacity_ / 4) {
            resize(capacity_ / 2);
        }
    }

public:
    // Big 5
    ABDQ()
        : data_(new T[1]), capacity_(1), size_(0), front_(0), back_(0) {}

    explicit ABDQ(std::size_t capacity)
        : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {}

    ABDQ(const ABDQ& other)
        : data_(new T[other.capacity_]),
          capacity_(other.capacity_),
          size_(other.size_),
          front_(0),
          back_(other.size_)
    {
        for (std::size_t i = 0; i < other.size_; i++) {
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }

    ABDQ(ABDQ&& other) noexcept
        : data_(other.data_),
          capacity_(other.capacity_),
          size_(other.size_),
          front_(other.front_),
          back_(other.back_)
    {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;

        T* newData = new T[other.capacity_];
        for (std::size_t i = 0; i < other.size_; i++) {
            newData[i] = other.data_[(other.front_ + i) % other.capacity_];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = 0;
        back_ = size_;

        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;

        delete[] data_;

        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    }

    ~ABDQ() override {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        ensureCapacity();
        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = item;
        size_++;
    }

    void pushBack(const T& item) override {
        ensureCapacity();
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("Deque is empty!");
        }

        T temp = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;

        shrinkIfNeeded();
        return temp;
    }

    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("Deque is empty!");
        }

        back_ = (back_ + capacity_ - 1) % capacity_;
        T temp = data_[back_];
        size_--;

        shrinkIfNeeded();
        return temp;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) throw std::runtime_error("Deque is empty!");
        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) throw std::runtime_error("Deque is empty!");
        return data_[(back_ + capacity_ - 1) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }
};
