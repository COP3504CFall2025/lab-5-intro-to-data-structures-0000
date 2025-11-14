#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    // Insertion
    void push(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T pop() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("Queue is empty");
        }
        T val = list.getHead()->data;
        list.removeHead();
        return val;
    }

    // Access
    const T& peek() const override {
        auto head = list.getHead();
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void printForward() const {
        list.printForward();
