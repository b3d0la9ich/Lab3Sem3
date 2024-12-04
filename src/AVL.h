#pragma once
#include <string>
#include <fstream>

class NodeAVL {
public:
    int key;
    int height;
    NodeAVL* left;
    NodeAVL* right;

    NodeAVL(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    NodeAVL* root; // Корневой узел дерева

    // Вспомогательные функции
    int height(NodeAVL* n) const;
    void updateHeight(NodeAVL* n);
    NodeAVL* rotateRight(NodeAVL* y);
    NodeAVL* rotateLeft(NodeAVL* x);
    NodeAVL* insert(NodeAVL* node, int key);
    NodeAVL* search(NodeAVL* node, int key) const;
    NodeAVL* minValueNode(NodeAVL* node) const;
    NodeAVL* deleteNode(NodeAVL* node, int key); // Вспомогательная функция для удаления
    void print(NodeAVL* node, int space = 0, int level = 0) const;
    void free(NodeAVL* node);

    // Методы для сериализации/десериализации
    void serializeToBinary(NodeAVL* node, std::ofstream& file) const;
    NodeAVL* deserializeFromBinary(std::ifstream& file);
    void serializeToText(NodeAVL* node, std::ofstream& file) const;
    NodeAVL* deserializeFromText(std::ifstream& file);

public:
    AVLTree();
    ~AVLTree();

    void insert(int key);
    void remove(int key); // Удаление элемента
    bool search(int key) const;
    void print() const;
    void clear();
    void writeToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    int getBalance(NodeAVL* n) const;
    NodeAVL* getRoot() const; // Получение корневого узла

    // Методы для сериализации/десериализации
    void serializeToBinary(const std::string& filename) const; // Сохранение в бинарный файл
    void deserializeFromBinary(const std::string& filename);   // Загрузка из бинарного файла
    void serializeToText(const std::string& filename) const;   // Сохранение в текстовый файл
    void deserializeFromText(const std::string& filename);     // Загрузка из текстового файла
};
