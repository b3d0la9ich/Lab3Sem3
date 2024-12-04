#include "AVL.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

// Конструктор
AVLTree::AVLTree() : root(nullptr) {}

// Деструктор
AVLTree::~AVLTree() {
    clear();
}

NodeAVL* AVLTree::getRoot() const {
    return root;
}

// Вспомогательная функция для получения высоты узла
int AVLTree::height(NodeAVL* n) const {
    return n ? n->height : 0;
}

// Вспомогательная функция для получения баланса узла
int AVLTree::getBalance(NodeAVL* n) const {
    return n ? height(n->left) - height(n->right) : 0;
}

// Вспомогательная функция для обновления высоты узла
void AVLTree::updateHeight(NodeAVL* n) {
    if (n) {
        n->height = 1 + max(height(n->left), height(n->right));
    }
}

NodeAVL* AVLTree::minValueNode(NodeAVL* node) const {
    NodeAVL* current = node;

    // Самый левый узел будет иметь минимальный ключ
    while (current && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

// Правое вращение
NodeAVL* AVLTree::rotateRight(NodeAVL* y) {
    NodeAVL* x = y->left;
    NodeAVL* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левое вращение
NodeAVL* AVLTree::rotateLeft(NodeAVL* x) {
    NodeAVL* y = x->right;
    NodeAVL* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Вставка элемента
void AVLTree::insert(int key) {
    root = insert(root, key);
}

NodeAVL* AVLTree::insert(NodeAVL* node, int key) {
    if (!node) return new NodeAVL(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Дубликаты не допускаются
    }

    updateHeight(node);

    int balance = getBalance(node);

    // Балансировка
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Поиск элемента
bool AVLTree::search(int key) const {
    return search(root, key) != nullptr;
}

NodeAVL* AVLTree::search(NodeAVL* node, int key) const {
    if (!node || node->key == key) {
        return node;
    }

    if (key < node->key) {
        return search(node->left, key);
    }

    return search(node->right, key);
}

// Удаление элемента
void AVLTree::remove(int key) {
    root = deleteNode(root, key);
}

NodeAVL* AVLTree::deleteNode(NodeAVL* node, int key) {
    if (!node) return node;

    // Ищем узел, который нужно удалить
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        // Узел найден
        if (!node->left || !node->right) {
            NodeAVL* temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp; // Копируем содержимое дочернего узла
            }
            delete temp;
        } else {
            // Узел с двумя детьми
            NodeAVL* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    if (!node) return node;

    // Обновляем высоту текущего узла
    updateHeight(node);

    // Проверяем баланс узла
    int balance = getBalance(node);

    // Балансировка узла
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}



// Печать дерева
void AVLTree::print() const {
    if (!root) {
        std::cout << ""; // Для пустого дерева ничего не выводим
        return;
    }
    print(root);
    std::cout << std::endl;
}


void AVLTree::print(NodeAVL* node, int space, int level) const {
    if (!node) return;

    space += 5;

    print(node->right, space, level + 1);

    cout << endl << setw(space) << node->key;

    print(node->left, space, level + 1);
}

// Очистка дерева
void AVLTree::clear() {
    free(root);
    root = nullptr;
}

void AVLTree::free(NodeAVL* node) {
    if (!node) return;

    free(node->left);
    free(node->right);

    delete node;
}

// Сохранение дерева в бинарный файл
void AVLTree::serializeToBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для записи");
    }
    serializeToBinary(root, file);
    file.close();
}

void AVLTree::serializeToBinary(NodeAVL* node, std::ofstream& file) const {
    if (!node) {
        int nullMarker = -1; // Используем -1 как маркер отсутствующего узла
        file.write(reinterpret_cast<const char*>(&nullMarker), sizeof(nullMarker));
        return;
    }

    file.write(reinterpret_cast<const char*>(&node->key), sizeof(node->key));
    serializeToBinary(node->left, file);
    serializeToBinary(node->right, file);
}

// Загрузка дерева из бинарного файла
void AVLTree::deserializeFromBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для чтения");
    }
    clear(); // Очищаем текущее дерево
    root = deserializeFromBinary(file);
    file.close();
}

NodeAVL* AVLTree::deserializeFromBinary(std::ifstream& file) {
    int key;
    if (!file.read(reinterpret_cast<char*>(&key), sizeof(key))) {
        return nullptr;
    }

    if (key == -1) { // Проверяем маркер отсутствующего узла
        return nullptr;
    }

    NodeAVL* node = new NodeAVL(key);
    node->left = deserializeFromBinary(file);
    node->right = deserializeFromBinary(file);
    updateHeight(node);
    return node;
}

// Сохранение дерева в текстовый файл (префиксный обход)
void AVLTree::serializeToText(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для записи");
    }
    serializeToText(root, file);
    file.close();
}

void AVLTree::serializeToText(NodeAVL* node, std::ofstream& file) const {
    if (!node) {
        file << "# "; // Используем символ '#' как маркер отсутствующего узла
        return;
    }

    file << node->key << " ";
    serializeToText(node->left, file);
    serializeToText(node->right, file);
}

// Загрузка дерева из текстового файла
void AVLTree::deserializeFromText(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла для чтения");
    }
    clear(); // Очищаем текущее дерево
    root = deserializeFromText(file);
    file.close();
}

NodeAVL* AVLTree::deserializeFromText(std::ifstream& file) {
    std::string token;
    if (!(file >> token) || token == "#") { // Проверяем маркер отсутствующего узла
        return nullptr;
    }

    int key = std::stoi(token);
    NodeAVL* node = new NodeAVL(key);
    node->left = deserializeFromText(file);
    node->right = deserializeFromText(file);
    updateHeight(node);
    return node;
}

