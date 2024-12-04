#pragma once
#include <string>

using namespace std;
const int TABLE_SIZE = 10;

class NodeHash {
public:
    string key;
    string value;
    NodeHash* next;

    NodeHash(const string& k, const string& v, NodeHash* n = nullptr)
        : key(k), value(v), next(n) {}
};

class HashTable {
private:
    NodeHash* table[TABLE_SIZE];

    int hashFunction(const string& key) const;

public:
    HashTable();
    ~HashTable();

    void insert(const string& key, const string& value);
    string get(const string& key) const;
    void remove(const string& key);
    void print() const;
    void clear();

    // Методы работы с файлами
    void writeToFile(const string& filename) const; // Запись в файл
    void loadFromFile(const std::string& filename); // Загрузка из файла

    // Методы сериализации
    void serializeToText(const std::string& filename) const; // Сериализация в текстовый файл
    void deserializeFromText(const std::string& filename);   // Десериализация из текстового файла
    void serializeToBinary(const std::string& filename) const; // Сериализация в бинарный файл
    void deserializeFromBinary(const std::string& filename);   // Десериализация из бинарного файла
};
