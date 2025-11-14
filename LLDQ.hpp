#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list(LinkedList<T>()) {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }

    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("List is empty");
        }

        T headData = list.getHead()->data;
        list.removeHead();
        return headData;
    }

    T popBack() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("List is empty");
        }

        T tailData = list.getTail()->data;
        list.removeTail();
        return tailData;
    }

    // Element Accessors
    const T& front() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("List is empty");
        }
        return list.getHead()->data;
    }

    const T& back() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("List is empty");
        }
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    // Debug functions
    void printForward() const {
        list.printForward();
    }

    void printReverse() const {
        list.printReverse();
    }
};
