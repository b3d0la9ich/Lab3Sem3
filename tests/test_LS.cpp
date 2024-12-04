#include <gtest/gtest.h>
#include "../src/LS.h"

// Тест: Добавление элемента в начало
TEST(DoubleListTest, AddToHead) {
    DoubleList list;
    list.addToHead(10);
    list.addToHead(20);
    list.addToHead(30);

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "30 20 10 \n");
}

// Тест: Добавление элемента в конец
TEST(DoubleListTest, AddToTail) {
    DoubleList list;
    list.addToTail(10);
    list.addToTail(20);
    list.addToTail(30);

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 30 \n");
}

// Тест: Удаление элемента с начала
TEST(DoubleListTest, RemoveFromHead) {
    DoubleList list;
    list.addToHead(10);
    list.addToHead(20);
    list.removeFromHead();

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 \n");
}

// Тест: Удаление элемента с конца
TEST(DoubleListTest, RemoveFromTail) {
    DoubleList list;
    list.addToTail(10);
    list.addToTail(20);
    list.removeFromTail();

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 \n");
}

// Тест: Удаление элемента по значению
TEST(DoubleListTest, RemoveByValue) {
    DoubleList list;
    list.addToTail(10);
    list.addToTail(20);
    list.addToTail(30);
    list.removeByValue(20);

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 30 \n");
}

// Тест: Поиск элемента
TEST(DoubleListTest, Find) {
    DoubleList list;
    list.addToTail(10);
    list.addToTail(20);

    EXPECT_TRUE(list.find(10));
    EXPECT_FALSE(list.find(30));
}

// Тест: Очистка списка
TEST(DoubleListTest, Clear) {
    DoubleList list;
    list.addToTail(10);
    list.addToTail(20);
    list.clear();

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

// Тест: Сохранение и загрузка из текстового файла
TEST(DoubleListTest, SerializeToTextAndDeserializeFromText) {
    DoubleList list;
    list.addToTail(10);
    list.addToTail(20);

    const std::string filename = "double_list_test.txt";
    list.serializeToText(filename);

    DoubleList newList;
    newList.deserializeFromText(filename);

    testing::internal::CaptureStdout();
    newList.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 \n");

    std::remove(filename.c_str());
}

// Тест: Сохранение и загрузка из бинарного файла
TEST(DoubleListTest, SerializeToBinaryAndDeserializeFromBinary) {
    DoubleList list;
    list.addToTail(10);
    list.addToTail(20);

    const std::string filename = "double_list_test.bin";
    list.serializeToBinary(filename);

    DoubleList newList;
    newList.deserializeFromBinary(filename);

    testing::internal::CaptureStdout();
    newList.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 \n");

    std::remove(filename.c_str());
}

// Тест: Пустой список
TEST(DoubleListTest, EmptyList) {
    DoubleList list;

    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}
