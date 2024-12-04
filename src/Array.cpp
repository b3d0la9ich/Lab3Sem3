#include "Array.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

// Конструктор
Array::Array(int initialCapacity) {
    if (initialCapacity <= 0) {
        throw invalid_argument("Вместимость должна быть положительным числом");
    }
    capacity = initialCapacity;
    size = 0;
    data = new int[capacity];
}

// Деструктор
Array::~Array() {
    delete[] data;
}

// Вспомогательная функция для увеличения емкости массива
void Array::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

// Добавить элемент в конец
void Array::append(int value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = value;
}

// Вставить элемент по индексу
void Array::insert(int index, int value) {
    if (index < 0 || index > size) {
        throw out_of_range("Индекс за пределами допустимого диапазона");
    }
    if (size >= capacity) {
        resize();
    }
    for (int i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++size;
}

// Получить элемент по индексу
int Array::get(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Индекс за пределами допустимого диапазона");
    }
    return data[index];
}

// Удалить элемент по индексу
void Array::remove(int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Индекс за пределами допустимого диапазона");
    }
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

// Заменить элемент по индексу
void Array::replace(int index, int value) {
    if (index < 0 || index >= size) {
        throw out_of_range("Индекс за пределами допустимого диапазона");
    }
    data[index] = value;
}

// Получить текущий размер массива
int Array::length() const {
    return size;
}

// Вывести массив в консоль
void Array::display() const {
    for (int i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}

// Записать массив в текстовый файл
void Array::serializeToText(const std::string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для записи");
    }
    for (int i = 0; i < size; ++i) {
        file << data[i] << endl;
    }
    file.close();
}

// Восстановить массив из текстового файла
void Array::deserializeFromText(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для чтения");
    }
    free(); // Очистим текущий массив перед загрузкой
    int value;
    while (file >> value) {
        append(value);
    }
    file.close();
}

// Записать массив в бинарный файл
void Array::serializeToBinary(const std::string& filename) const {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для записи");
    }
    file.write(reinterpret_cast<const char*>(&size), sizeof(size)); // Сначала записываем размер
    file.write(reinterpret_cast<const char*>(data), sizeof(int) * size); // Записываем элементы массива
    file.close();
}

// Восстановить массив из бинарного файла
void Array::deserializeFromBinary(const std::string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Ошибка при открытии файла для чтения");
    }
    free(); // Очистим текущий массив перед загрузкой
    file.read(reinterpret_cast<char*>(&size), sizeof(size)); // Считываем размер
    capacity = size > 0 ? size : 1; // Устанавливаем емкость
    data = new int[capacity]; // Выделяем новую память
    file.read(reinterpret_cast<char*>(data), sizeof(int) * size); // Считываем элементы массива
    file.close();
}

// Очистить массив
void Array::free() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}
