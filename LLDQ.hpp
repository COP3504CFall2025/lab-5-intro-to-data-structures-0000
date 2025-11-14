#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLDQ() = default;

    // Insertion
    void pushFront(const T& item) override {
        list.addHead(item);
    }

    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T popFront() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Deque is empty");
        }
        T val = list.getHead()->data;
        list.removeHead();
        return val;
    }

    T popBack() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Deque is empty");
        }
        T val = list.getTail()->data;
        list.removeTail();
        return val;
    }

    // Access
    const T& front() const override {
        auto head = list.getHead();
        if (!head) {
            throw std::runtime_error("Deque is empty");
        }
        return head->data;
    }

    const T& back() const override {
        auto tail = list.getTail();
        if (!tail) {
            throw std::runtime_error("Deque is empty");
        }
        return tail->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void printForward() const {
        list.printForward();
    }

    void printReverse() const {
        list.printReverse();
    }
};
