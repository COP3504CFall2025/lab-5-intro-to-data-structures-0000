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
    LLS() : list(LinkedList<T>()) {}

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("List is empty");
        }

        const auto* head = list.getHead();
        T headData = head->data;
        list.removeHead();
        return headData;
    }

    // Access
    T peek() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("List is empty");
        }

        const auto* head = list.getHead();
        return head->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    // Debug functions
    void printForward() const {
        list.printForward();
    }

    void printBackward() const {
        list.printReverse();
    }
};
