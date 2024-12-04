#pragma once
#include <iostream>
#include <string>
#include "Node.h"

// Класс Очередь
class Queue {
private:
    Node* head;      // Указатель на начало очереди
    Node* tail;      // Указатель на конец очереди

public:
    // Конструкторы и деструктор
    Queue();                      // Конструктор
    ~Queue();                     // Деструктор

    // Операции с очередью
    void enqueue(int item);       // Добавить элемент в очередь
    int dequeue();                // Удалить элемент из очереди
    void print() const;           // Вывести содержимое очереди

    // Сериализация и десериализация
    void serializeToText(const std::string& filename) const;  // Сохранить очередь в текстовый файл
    void deserializeFromText(const std::string& filename);    // Загрузить очередь из текстового файла
    void serializeToBinary(const std::string& filename) const; // Сохранить очередь в бинарный файл
    void deserializeFromBinary(const std::string& filename);   // Загрузить очередь из бинарного файла

    // Управление памятью
    void clear();                 // Очистить очередь
};
