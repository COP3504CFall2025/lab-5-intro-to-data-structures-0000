#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = list(LinkedList<T>()) {};

    // Insertion
    void push(const T& item) override {
		list.addHead(item);
	}

    // Deletion
    T pop() override [
		if (list.getCount() == 0) {
			throw std::runtime_error("List is empty cannot pop element");
		}

		const Node<T>* head = list.getHead();
		T HeadData = head->data;
		list.removeHead();
		return headData;
	}

    // Access
    T peek() const override {
		if (list.getCount() == 0 {
			throw std::runtime_error("List is empty cannot pop element");
		}

		const Node<T>* head = list.getHead();
		return head->data;

    //Getters
    std::size_t getSize() const noexcept override;

	void printForward() const {
		list.printForward();
	}

	void printBackward() const {
		list.printReverse();
	}
};