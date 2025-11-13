#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    public:
        T data;
		Node<T>* prev;
		Node<T>* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
	if (head == nullptr) return;

    Node<T>* cur = head;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
}
	void printReverse() const {
	if (tail == nullptr) return;
	Node<T>* cur = tail;
	while (cur) {
		cout << cur->data << " ";
		cur = cur->prev;
	}
}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
	if (head == nullptr) return 0;
	Node<T>* cur = head;
	unsigned int count = 0;
	while (cur != nullptr) {
		cur = cur->next;
		count++;
	}
	return count;
}
	Node<T>* getHead() {
	return head;
}
	const Node<T>* getHead() const {
	return head;
}
	Node<T>* getTail() {
	return tail;
}
	const Node<T>* getTail() const {
	return tail;
}

	// Insertion
	void addHead(const T& data) {
	Node<T>* newNode = new Node(data);
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->prev = head;
		head = newNode;
	}
	++count;
}
	void addTail(const T& data) {
	Node<T>* newNode = new Node(data);
	if (tail == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->next = head;
		tail = newNode;
	}
	++count;
}

	// Removal
	bool removeHead() {
	if (head == nullptr) return false;
	Node* cur = head;
	head = cur->next;
	cur = null ptr;
	delete cur;
	return true;
	--count;
}
	bool removeTail() {
	if (tail == nullptr) return false;
	Node<T>* cur = tail;
	tail = cur->prev;
	tail = nullptr;
	delete cur;
	return true;
	--count;
}
	void Clear() {
	Node<T>* cur = head;
    while (cur != nullptr) {
    	Node* next = cur->next;
		delete next;
		cur = cur->next;
    }
	head = nullptr;
	tail = nullptr;
	count = 0;
}

	// Operators
//copy assignment
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
	if (this == &other) {
		return *this;
	}
	Clear();
	head = move(other.head);
	tail = move(other.tail);
	other.head = nullptr;
	other.tail = nullptr;
	return *this;
}
//move assignment
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
	Clear();
	head = other.head;
    tail = other.tail;
    count = other.count;
    other.head = other.tail = nullptr;
    other.count = 0;
    return *this;
}

	// Construction/Destruction
	LinkedList() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}
	LinkedList(const LinkedList<T>& list) {
	for (T& data : list) {
		addHead(data);
	}
}
	LinkedList(LinkedList<T>&& other) noexcept {
	head = (other.head);
	tail = (other.tail);
	other.head = nullptr;
	other.tail = nullptr;
}
	~LinkedList() {
	Clear();
}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};