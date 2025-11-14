#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list(LinkedList<T>()) {}

    // Insertion
    void enqueue(const T& item) override {
		list.addTail(item);
	}
    // Deletion
    T dequeue() override {
		if (list.getCount() == 0) {
			throw std::runtime_error("List is empty");
		}

		T headData = list.getHead()->data;

		list.removeHead();
		return headData;
	}

    // Access
    T peek() const override {
		if (list.getCount() == 0) {
			throw std::runtime_error("List is empty");
		}

		const Node<T>* head = list.getHead();
		return head->data;
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