#include <iostream>

//
// Created by alice on 24.09.2025.
//

struct Node {
    int value;
    Node *next;

    explicit Node(int val) : value(val), next(nullptr) {}
};

class List {
private:
    Node *head;
    Node *tail;

public:
    List() : head(nullptr), tail(nullptr) {}

    [[nodiscard]] bool empty() const {
        return head == nullptr;
    }

    void print() const {
        Node *current = head;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void push_front(int value) {
        Node *newNode = new Node(value);

        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }

    void push_back(int value) {
        Node *newNode = new Node(value);

        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void pop_front() {
        if (empty()) return;

        Node *temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void pop_back() {
        if (empty()) return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node *current = head;
        while (current->next != tail) {
            current = current->next;
        }

        delete tail;
        tail = current;
        tail->next = nullptr;
    }

    [[nodiscard]] int get() const {
        if (empty()) {
            return -1;
        }

        int count = 0;
        Node *current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }

        int middleIndex = count / 2;
        current = head;
        for (int i = 0; i < middleIndex; i++) {
            current = current->next;
        }

        return current->value;
    }

    ~List() {
        while (!empty()) {
            pop_front();
        }
    }
};

int main() {
    List list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_front(5);

    list.print();

    std::cout << "Средний элемент: " << list.get() << std::endl;

    list.pop_front();
    list.print();
    list.pop_back();
    list.print();


    return 0;
}