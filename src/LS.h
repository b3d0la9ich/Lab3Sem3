#pragma once
#include <string>

class NodeL2 {
public:
    int data;
    NodeL2* next;
    NodeL2* previous;

    NodeL2(int value, NodeL2* nextNode = nullptr, NodeL2* prevNode = nullptr)
        : data(value), next(nextNode), previous(prevNode) {}
};

class DoubleList {
private:
    NodeL2* head; // Указатель на начало списка
    NodeL2* tail; // Указатель на конец списка

public:
    DoubleList();                      // Конструктор
    ~DoubleList();                     // Деструктор

    void addToHead(int value);         // Добавить элемент в начало
    void addToTail(int value);         // Добавить элемент в конец
    void removeFromHead();             // Удалить элемент с начала
    void removeFromTail();             // Удалить элемент с конца
    void removeByValue(int value);     // Удалить элемент по значению
    bool find(int value) const;        // Найти элемент по значению
    void print() const;                // Печать всех элементов
    void clear();                      // Очистить список

    // Методы для сериализации и десериализации
    void serializeToText(const std::string& filename) const;  // Сохранить список в текстовый файл
    void deserializeFromText(const std::string& filename);    // Загрузить список из текстового файла
    void serializeToBinary(const std::string& filename) const; // Сохранить список в бинарный файл
    void deserializeFromBinary(const std::string& filename);   // Загрузить список из бинарного файла
};
