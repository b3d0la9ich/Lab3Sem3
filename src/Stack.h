#pragma once
#include <string>

class Stack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* top; // Верхний элемент стека

public:
    Stack();
    ~Stack();

    void push(int value);
    void pop();
    void print() const;
    void clear();

    // Методы сериализации и десериализации
    void serializeToText(const std::string& filename) const;
    void deserializeFromText(const std::string& filename);
    void serializeToBinary(const std::string& filename) const;
    void deserializeFromBinary(const std::string& filename);
};
