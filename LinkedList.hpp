#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node<T>* next;
        Node<T>* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node<T>* head;
    Node<T>* tail;
    unsigned int count;

public:
    // Behaviors
    void printForward() const {
        if (!head) return;
        Node<T>* cur = head;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }

    void printReverse() const {
        if (!tail) return;
        Node<T>* cur = tail;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->prev;
        }
        cout << endl;
    }

    // Accessors
    [[nodiscard]] unsigned int getCount() const {
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
        Node<T>* n = new Node(data);

        n->next = head;
        if (head) head->prev = n;
        head = n;

        if (!tail) tail = n;

        count++;
    }

    void addTail(const T& data) {
        Node<T>* n = new Node(data);

        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;

        if (!head) head = n;

        count++;
    }

    // Removal
    bool removeHead() {
        if (!head) return false;

        Node<T>* cur = head;
        head = head->next;

        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;

        delete cur;
        count--;
        return true;
    }

    bool removeTail() {
        if (!tail) return false;

        Node<T>* cur = tail;
        tail = tail->prev;

        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;

        delete cur;
        count--;
        return true;
    }

    void Clear() {
        Node<T>* cur = head;
        while (cur) {
            Node<T>* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        count = 0;
    }

    // Operators
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
        if (this != &other) {
            Clear();
            head = other.head;
            tail = other.tail;
            count = other.count;

            other.head = nullptr;
            other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    LinkedList<T>& operator=(const LinkedList<T>& rhs) {
        if (this != &rhs) {
            Clear();
            Node<T>* cur = rhs.head;
            while (cur) {
                addTail(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    // Construction / Destruction
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
        Node<T>* cur = list.head;
        while (cur) {
            addTail(cur->data);
            cur = cur->next;
        }
    }

    LinkedList(LinkedList<T>&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }

    ~LinkedList() {
        Clear();
    }
};
