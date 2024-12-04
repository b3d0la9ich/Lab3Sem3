#include <gtest/gtest.h>
#include "../src/AVL.h"

// Тест: Проверка вставки и поиска
TEST(AVLTreeTest, InsertAndSearch) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(5));
    EXPECT_FALSE(tree.search(15)); // Элемент отсутствует
}

// Тест: Проверка удаления
TEST(AVLTreeTest, Remove) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.remove(10);

    EXPECT_FALSE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(5));
}

// Тест: Проверка балансировки
TEST(AVLTreeTest, Balancing) {
    AVLTree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10); // Требуется правое вращение

    EXPECT_TRUE(tree.search(30));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(10));
}

// Тест: Очистка дерева
TEST(AVLTreeTest, Clear) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    tree.clear();

    EXPECT_FALSE(tree.search(10));
    EXPECT_FALSE(tree.search(20));
    EXPECT_FALSE(tree.search(5));
}

// Тест: Сериализация в текстовый файл и десериализация из него
TEST(AVLTreeTest, SerializeAndDeserializeText) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    std::string filename = "avltree_test.txt";
    tree.serializeToText(filename);

    AVLTree newTree;
    newTree.deserializeFromText(filename);

    EXPECT_TRUE(newTree.search(10));
    EXPECT_TRUE(newTree.search(20));
    EXPECT_TRUE(newTree.search(5));
    EXPECT_FALSE(newTree.search(15));

    std::remove(filename.c_str()); // Удаление тестового файла
}

// Тест: Сериализация в бинарный файл и десериализация из него
TEST(AVLTreeTest, SerializeAndDeserializeBinary) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    std::string filename = "avltree_test.bin";
    tree.serializeToBinary(filename);

    AVLTree newTree;
    newTree.deserializeFromBinary(filename);

    EXPECT_TRUE(newTree.search(10));
    EXPECT_TRUE(newTree.search(20));
    EXPECT_TRUE(newTree.search(5));
    EXPECT_FALSE(newTree.search(15));

    std::remove(filename.c_str()); // Удаление тестового файла
}

// Тест: Проверка корректности печати дерева
TEST(AVLTreeTest, PrintTree) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    testing::internal::CaptureStdout();
    tree.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("20"), std::string::npos);
    EXPECT_NE(output.find("5"), std::string::npos);
}

TEST(AVLTreeTest, RotateLeft) {
    AVLTree tree;

    // Создаем сценарий для левого вращения
    tree.insert(10); // Корневой узел
    tree.insert(20); // Правая ветвь
    tree.insert(30); // Провоцируем левое вращение

    // Проверяем структуру дерева после левого вращения
    NodeAVL* root = tree.getRoot();
    ASSERT_NE(root, nullptr); // Проверяем, что корень существует
    EXPECT_EQ(root->key, 20); // После вращения 20 становится корнем
    EXPECT_EQ(root->left->key, 10); // Левый ребенок - 10
    EXPECT_EQ(root->right->key, 30); // Правый ребенок - 30
}

TEST(AVLTreeTest, LeftRightRotation) {
    AVLTree tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(20); // Левое-правое вращение на узле 30

    EXPECT_EQ(tree.getRoot()->key, 20); // Корнем должно стать 20
    EXPECT_EQ(tree.getRoot()->left->key, 10); // Левый ребенок 20 - это 10
    EXPECT_EQ(tree.getRoot()->right->key, 30); // Правый ребенок 20 - это 30
}

TEST(AVLTreeTest, RightLeftRotation) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(30);
    tree.insert(20); // Правое-левое вращение на узле 10

    EXPECT_EQ(tree.getRoot()->key, 20); // Корнем должно стать 20
    EXPECT_EQ(tree.getRoot()->left->key, 10); // Левый ребенок 20 - это 10
    EXPECT_EQ(tree.getRoot()->right->key, 30); // Правый ребенок 20 - это 30
}

TEST(AVLTreeTest, ComplexInsertSequence) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    EXPECT_EQ(tree.getRoot()->key, 30); // Корень должен быть 30
    EXPECT_EQ(tree.getRoot()->left->key, 20); // Левый ребенок 30 - это 20
    EXPECT_EQ(tree.getRoot()->right->key, 40); // Правый ребенок 30 - это 40
    EXPECT_EQ(tree.getRoot()->left->left->key, 10); // Левый ребенок 20 - это 10
    EXPECT_EQ(tree.getRoot()->left->right->key, 25); // Правый ребенок 20 - это 25
    EXPECT_EQ(tree.getRoot()->right->right->key, 50); // Правый ребенок 40 - это 50
}

TEST(AVLTreeTest, EmptyTree) {
    AVLTree tree;

    testing::internal::CaptureStdout();
    tree.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // Исправлено на пустую строку без перевода строки
}

TEST(AVLTreeTest, NoDuplicatesAllowed) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(10); // Попытка вставить дубликат

    EXPECT_EQ(tree.search(10), true); // Ключ 10 должен существовать
    EXPECT_EQ(tree.getRoot()->key, 10); // Корень дерева - 10
}


