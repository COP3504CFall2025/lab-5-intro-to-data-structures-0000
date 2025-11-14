#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    unsigned int count;

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
        Node* n = new Node(data);

        n->next = head;
        if (head) head->prev = n;
        head = n;

        if (!tail) tail = n;

        count++;
    }

    void addTail(const T& data) {
        Node* n = new Node(data);

        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;

        if (!head) head = n;

        count++;
    }

    // Removal
    bool removeHead() {
        if (!head) return false;

        Node* cur = head;
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

        Node* cur = tail;
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
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
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
            Node* cur = rhs.head;
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
        Node* cur = list.head;
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
