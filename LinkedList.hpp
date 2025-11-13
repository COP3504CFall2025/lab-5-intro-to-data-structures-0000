#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:

    // --- Behaviors ---
    void printForward() const {
        Node<T>* cur = head;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
    }

    void printReverse() const {
        Node<T>* cur = tail;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->prev;
        }
    }

    // --- Accessors ---
    [[nodiscard]] unsigned int getCount() const {
        return count;
    }

    Node<T>* getHead() { return head; }
    const Node<T>* getHead() const { return head; }

    Node<T>* getTail() { return tail; }
    const Node<T>* getTail() const { return tail; }

    // --- Insertion ---
    void addHead(const T& data) {
        Node<T>* newNode = new Node<T>(data);

        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        ++count;
    }

    void addTail(const T& data) {
        Node<T>* newNode = new Node<T>(data);

        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        ++count;
    }

    // --- Removal ---
    bool removeHead() {
        if (!head) return false;

        Node<T>* temp = head;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        --count;
        return true;
    }

    bool removeTail() {
        if (!tail) return false;

        Node<T>* temp = tail;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
        --count;
        return true;
    }

    void Clear() {
        Node<T>* cur = head;

        while (cur) {
            Node<T>* next = cur->next;
            delete cur;
            cur = next;
        }

        head = tail = nullptr;
        count = 0;
    }

    // --- Operators ---
    // Move assignment
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
        if (this == &other) return *this;

        Clear();
        head = other.head;
        tail = other.tail;
        count = other.count;

        other.head = other.tail = nullptr;
        other.count = 0;

        return *this;
    }

    // Copy assignment
    LinkedList<T>& operator=(const LinkedList<T>& rhs) {
        if (this == &rhs) return *this;

        Clear();

        Node<T>* cur = rhs.head;
        while (cur) {
            addTail(cur->data);
            cur = cur->next;
        }

        return *this;
    }

    // --- Constructors/Destructor ---
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // Copy constructor
    LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
        Node<T>* cur = list.head;
        while (cur) {
            addTail(cur->data);
            cur = cur->next;
        }
    }

    // Move constructor
    LinkedList(LinkedList<T>&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count)
    {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    ~LinkedList() {
        Clear();
    }

private:
    Node<T>* head;
    Node<T>* tail;
    unsigned int count;
};
