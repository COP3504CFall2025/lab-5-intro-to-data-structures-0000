#pragma once
#include <iostream>
using namespace std;


template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
	if (!head) return;

    Node* cur = head;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}
	void printReverse() const {
	if (!tail) return;
	Node* cur = tail;
	while (cur != nullptr) {
		cout << cur->data << " ";
		cur = cur->prev;
	}
}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
	if (head == nullptr) return 0;
	Node* cur = head;
	unsigned int count = 0;
	while (cur != nullptr) {
		cur = cur->next;
		count++;
	}
	return count;
}
	Node* getHead() {
	return head;
}
	const Node* getHead() const {
	return head;
}
	Node* getTail() {
	return tail;
}
	const Node* getTail() const {
	return tail;
}

	// Insertion
	void addHead(const T& data) {

}
	void addTail(const T& data) {

}

	// Removal
	bool removeHead() {
	if (head == nullptr) return false;
	Node* cur = head;
	head = cur->next;
	delete cur;
	return true;
}
	bool removeTail() {
	if (tail == nullptr) return false;
	Node* cur = tail;
	tail = cur->prev;
	delete cur;
	return true;
}
	void Clear() {
	Node* cur = head;
    while (cur) {
        delete cur;
		cur = cur->next;
    }
}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept;
	~LinkedList();

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


