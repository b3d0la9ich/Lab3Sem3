#include "Array.h"
#include <fstream>
#include <stdexcept>

// Конструктор
Array::Array(int initialCapacity) {
    if (initialCapacity <= 0) {
        throw std::invalid_argument("Вместимость должна быть положительным числом");
    }
    capacity = initialCapacity;
    size = 0;
    data = new int[capacity];
}

// Деструктор
Array::~Array() {
    delete[] data;
}

// Увеличение емкости
void Array::resize() {
    // важный фикс: из нуля вырастим до 1, иначе capacity *= 2 оставит 0
    if (capacity == 0) capacity = 1;
    capacity *= 2;
    int* newData = new int[capacity];
    for (int i = 0; i < size; ++i) newData[i] = data[i];
    delete[] data;
    data = newData;
}

// Добавить элемент в конец
void Array::append(int value) {
    if (size >= capacity) resize();
    data[size++] = value;
}

// Вставить элемент по индексу
void Array::insert(int index, int value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Индекс за пределами допустимого диапазона");
    }
    if (size >= capacity) resize();
    for (int i = size; i > index; --i) data[i] = data[i - 1];
    data[index] = value;
    ++size;
}

// Получить элемент по индексу
int Array::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс за пределами допустимого диапазона");
    }
    return data[index];
}

// Удалить элемент по индексу
void Array::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс за пределами допустимого диапазона");
    }
    for (int i = index; i < size - 1; ++i) data[i] = data[i + 1];
    --size;
}

// Заменить элемент по индексу
void Array::replace(int index, int value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс за пределами допустимого диапазона");
    }
    data[index] = value;
}

// Текущий размер
int Array::length() const {
    return size;
}

void Array::display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << '\n';
}

// Требуемый main.cpp метод: записываем в текстовый файл
void Array::writeToFile(const std::string& filename) const {
    serializeToText(filename);
}

// --- Сериализация в текст
void Array::serializeToText(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для записи: " + filename);
    }
    for (int i = 0; i < size; ++i) {
        file << data[i] << '\n';
    }
}

// Загрузка из текста
void Array::deserializeFromText(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для чтения: " + filename);
    }
    free(); // обнулим и начнем заполнять
    int value;
    while (file >> value) append(value);
}

// Сериализация в бинарный файл
void Array::serializeToBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для записи: " + filename);
    }
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));         // сначала размер
    file.write(reinterpret_cast<const char*>(data), sizeof(int) * size);    // затем данные
}

// Загрузка из бинарного файла
void Array::deserializeFromBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для чтения: " + filename);
    }

    // читаем новый размер
    int newSize = 0;
    file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    if (!file) {
        throw std::runtime_error("Не удалось прочитать размер массива из: " + filename);
    }

    // подготовим емкость и буфер
    delete[] data;                 // очистим старые данные
    size = newSize;
    capacity = (newSize > 0) ? newSize : 1;
    data = new int[capacity];

    if (newSize > 0) {
        file.read(reinterpret_cast<char*>(data), sizeof(int) * newSize);
        if (!file) {
            throw std::runtime_error("Не удалось прочитать данные массива из: " + filename);
        }
    }
}

// Очистка массива (оставим валидное состояние)
void Array::free() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;  // допустимо: resize() умеет поднимать 0 -> 1 -> 2...
}
