#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T pop() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Stack is empty");
        }
        T val = list.getTail()->data;
        list.removeTail();
        return val;
    }

    // Access
    const T& peek() const override {
        auto tail = list.getTail();
        if (!tail) {
            throw std::runtime_error("Stack is empty");
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
