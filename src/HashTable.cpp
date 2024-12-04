#include "HashTable.h"
#include <iostream>
#include <fstream>

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
}

int HashTable::hashFunction(const std::string& key) const {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}

void HashTable::insert(const std::string& key, const std::string& value) {
    int index = hashFunction(key);
    NodeHash* newNode = new NodeHash(key, value);

    if (!table[index]) {
        table[index] = newNode;
    } else {
        NodeHash* current = table[index];
        while (current) {
            if (current->key == key) {
                current->value = value; // Обновляем значение, если ключ найден
                delete newNode;
                return;
            }
            if (!current->next) break;
            current = current->next;
        }
        current->next = newNode;
    }
}

std::string HashTable::get(const std::string& key) const {
    int index = hashFunction(key);
    NodeHash* current = table[index];

    while (current) {
        if (current->key == key) return current->value;
        current = current->next;
    }
    return "Ключ не найден";
}

void HashTable::remove(const std::string& key) {
    int index = hashFunction(key);
    NodeHash* current = table[index];
    NodeHash* prev = nullptr;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void HashTable::print() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        std::cout << "Index " << i << ": ";
        NodeHash* current = table[i];
        while (current) {
            std::cout << "[" << current->key << ": " << current->value << "] ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeHash* current = table[i];
        while (current) {
            NodeHash* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        table[i] = nullptr;
    }
}

// Сериализация в текстовый файл
void HashTable::serializeToText(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для записи");
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeHash* current = table[i];
        while (current) {
            file << current->key << " " << current->value << std::endl;
            current = current->next;
        }
    }
    file.close();
}

// Десериализация из текстового файла
void HashTable::deserializeFromText(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для чтения");
    }

    clear(); // Очистим текущую таблицу
    std::string key, value;
    while (file >> key >> value) {
        insert(key, value);
    }
    file.close();
}

// Сериализация в бинарный файл
void HashTable::serializeToBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для записи");
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeHash* current = table[i];
        while (current) {
            size_t keySize = current->key.size();
            size_t valueSize = current->value.size();

            file.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
            file.write(current->key.c_str(), keySize);
            file.write(reinterpret_cast<const char*>(&valueSize), sizeof(valueSize));
            file.write(current->value.c_str(), valueSize);

            current = current->next;
        }
    }
    file.close();
}

// Десериализация из бинарного файла
void HashTable::deserializeFromBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для чтения");
    }

    clear(); // Очистим текущую таблицу
    while (file.peek() != EOF) {
        size_t keySize, valueSize;
        file.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));

        std::string key(keySize, '\0');
        file.read(&key[0], keySize);

        file.read(reinterpret_cast<char*>(&valueSize), sizeof(valueSize));

        std::string value(valueSize, '\0');
        file.read(&value[0], valueSize);

        insert(key, value);
    }
    file.close();
}
