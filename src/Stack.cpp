#include "Stack.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Определения всех методов Stack
Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    clear();
}

void Stack::push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;
    top = newNode;
}

void Stack::pop() {
    if (top == nullptr) {
        throw underflow_error("Стек пуст");
    }
    Node* temp = top;
    top = top->next;
    delete temp;
}

void Stack::print() const {
    if (top == nullptr) {
        cout << "Стек пуст" << endl;
        return;
    }
    Node* temp = top;
    cout << "Элементы стека: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void Stack::serializeToText(const std::string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для записи");
    }

    Node* temp = top;
    while (temp != nullptr) {
        file << temp->data << endl;
        temp = temp->next;
    }

    file.close();
}

void Stack::deserializeFromText(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для чтения");
    }

    clear();

    int value;
    while (file >> value) {
        push(value);
    }

    file.close();
}

void Stack::serializeToBinary(const std::string& filename) const {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для записи");
    }

    Node* temp = top;
    while (temp != nullptr) {
        file.write(reinterpret_cast<const char*>(&temp->data), sizeof(temp->data));
        temp = temp->next;
    }

    file.close();
}

void Stack::deserializeFromBinary(const std::string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для чтения");
    }

    clear();

    int value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        push(value);
    }

    file.close();
}

void Stack::clear() {
    while (top != nullptr) {
        pop();
    }
}
