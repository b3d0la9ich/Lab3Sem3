#include <gtest/gtest.h>
#include "../src/LO.h" // Предполагается, что ваш класс находится в src/LO.h
#include <fstream>

// Тест: Проверка добавления элементов в начало
TEST(ListOneTest, AddToHead) {
    ListOne list;
    list.addToHead(10);
    list.addToHead(20);

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "20 10 \n");
}

// Тест: Проверка добавления элементов в конец
TEST(ListOneTest, AddToTail) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "10 20 \n");
}

// Тест: Проверка удаления элемента с головы
TEST(ListOneTest, RemoveHead) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);
    list.removeHead();

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "20 \n");
}

// Тест: Проверка удаления элемента с хвоста
TEST(ListOneTest, RemoveTail) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);
    list.removeTail();

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "10 \n");
}

// Тест: Проверка удаления элемента по значению
TEST(ListOneTest, RemoveByValue) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);
    list.addToTail(30);
    list.removeByValue(20);

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "10 30 \n");
}

// Тест: Проверка поиска элемента
TEST(ListOneTest, Search) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);

    EXPECT_TRUE(list.search(10));
    EXPECT_TRUE(list.search(20));
    EXPECT_FALSE(list.search(30));
}

// Тест: Проверка очистки списка
TEST(ListOneTest, Clear) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);
    list.clear();

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "");
}

// Тест: Проверка сериализации и десериализации в текстовый файл
TEST(ListOneTest, SerializeDeserializeText) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);

    const std::string filename = "test_list.txt";
    list.serializeToText(filename);

    ListOne newList;
    newList.deserializeFromText(filename);

    testing::internal::CaptureStdout();
    newList.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "10 20 \n");

    std::remove(filename.c_str()); // Удаление тестового файла
}

// Тест: Проверка сериализации и десериализации в бинарный файл
TEST(ListOneTest, SerializeDeserializeBinary) {
    ListOne list;
    list.addToTail(10);
    list.addToTail(20);

    const std::string filename = "test_list.bin";
    list.serializeToBinary(filename);

    ListOne newList;
    newList.deserializeFromBinary(filename);

    testing::internal::CaptureStdout();
    newList.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "10 20 \n");

    std::remove(filename.c_str()); // Удаление тестового файла
}

// Тест: Проверка печати пустого списка
TEST(ListOneTest, EmptyListPrint) {
    ListOne list;

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "");
}

// Тест: Удаление первого элемента списка
TEST(ListOneTest, RemoveByValueHead) {
    ListOne list;
    list.addToHead(10);
    list.addToHead(20);
    list.addToHead(30); // Список: 30 -> 20 -> 10

    list.removeByValue(30); // Удаляем первый элемент (голову)

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "20 10 \n"); // Ожидается: 20 -> 10
}

// Тест: Удаление элемента из середины
TEST(ListOneTest, RemoveByValueMiddle) {
    ListOne list;
    list.addToHead(10);
    list.addToHead(20);
    list.addToHead(30); // Список: 30 -> 20 -> 10

    list.removeByValue(20); // Удаляем средний элемент

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "30 10 \n"); // Ожидается: 30 -> 10
}

// Тест: Удаление последнего элемента
TEST(ListOneTest, RemoveByValueTail) {
    ListOne list;
    list.addToHead(10);
    list.addToHead(20);
    list.addToHead(30); // Список: 30 -> 20 -> 10

    list.removeByValue(10); // Удаляем последний элемент

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "30 20 \n"); // Ожидается: 30 -> 20
}

// Тест: Удаление элемента, которого нет в списке
TEST(ListOneTest, RemoveByValueNotFound) {
    ListOne list;
    list.addToHead(10);
    list.addToHead(20);
    list.addToHead(30); // Список: 30 -> 20 -> 10

    list.removeByValue(40); // Удаляем элемент, которого нет

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "30 20 10 \n"); // Список остается неизменным
}

// Тест: Удаление из пустого списка
TEST(ListOneTest, RemoveByValueEmptyList) {
    ListOne list;

    list.removeByValue(10); // Пытаемся удалить из пустого списка

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // Список остается пустым
}
