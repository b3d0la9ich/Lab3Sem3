#include <gtest/gtest.h>
#include <fstream>
#include "../src/Array.h"

// Тест: Проверка метода insert
TEST(ArrayTest, Insert) {
    Array arr(3);

    // Вставка в пустой массив
    arr.insert(0, 10);
    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.get(0), 10);

    // Вставка в начало массива
    arr.insert(0, 5);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.get(0), 5);
    EXPECT_EQ(arr.get(1), 10);

    // Вставка в конец массива
    arr.insert(2, 20);
    EXPECT_EQ(arr.length(), 3);
    EXPECT_EQ(arr.get(2), 20);

    // Вставка в середину массива
    arr.insert(1, 15);
    EXPECT_EQ(arr.length(), 4);
    EXPECT_EQ(arr.get(0), 5);
    EXPECT_EQ(arr.get(1), 15);
    EXPECT_EQ(arr.get(2), 10);
    EXPECT_EQ(arr.get(3), 20);

    // Проверка выброса исключений
    EXPECT_THROW(arr.insert(-1, 0), std::out_of_range);
    EXPECT_THROW(arr.insert(5, 0), std::out_of_range);
}

// Тест: Проверка метода get
TEST(ArrayTest, Get) {
    Array arr(3);

    // Добавление элементов
    arr.append(10);
    arr.append(20);
    arr.append(30);

    // Проверка получения элементов
    EXPECT_EQ(arr.get(0), 10);
    EXPECT_EQ(arr.get(1), 20);
    EXPECT_EQ(arr.get(2), 30);

    // Проверка выброса исключений
    EXPECT_THROW(arr.get(-1), std::out_of_range);
    EXPECT_THROW(arr.get(3), std::out_of_range);
}

// Тест: Проверка текстовой сериализации и десериализации
TEST(ArrayTest, SerializeToTextAndDeserializeFromText) {
    Array arr(5);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    std::string filename = "test_array.txt";

    // Сериализация
    EXPECT_NO_THROW(arr.serializeToText(filename));

    // Создаем новый массив для десериализации
    Array newArr(5);
    EXPECT_NO_THROW(newArr.deserializeFromText(filename));

    // Проверяем, что данные восстановлены корректно
    EXPECT_EQ(newArr.length(), 3);
    EXPECT_EQ(newArr.get(0), 10);
    EXPECT_EQ(newArr.get(1), 20);
    EXPECT_EQ(newArr.get(2), 30);

    // Удаляем временный файл
    std::remove(filename.c_str());
}

// Тест: Проверка бинарной сериализации и десериализации
TEST(ArrayTest, SerializeToBinaryAndDeserializeFromBinary) {
    Array arr(5);
    arr.append(40);
    arr.append(50);
    arr.append(60);

    std::string filename = "test_array.bin";

    // Сериализация
    EXPECT_NO_THROW(arr.serializeToBinary(filename));

    // Создаем новый массив для десериализации
    Array newArr(5);
    EXPECT_NO_THROW(newArr.deserializeFromBinary(filename));

    // Проверяем, что данные восстановлены корректно
    EXPECT_EQ(newArr.length(), 3);
    EXPECT_EQ(newArr.get(0), 40);
    EXPECT_EQ(newArr.get(1), 50);
    EXPECT_EQ(newArr.get(2), 60);

    // Удаляем временный файл
    std::remove(filename.c_str());
}

// Тест: Проверка работы с пустым массивом при сериализации и десериализации
TEST(ArrayTest, SerializeEmptyArray) {
    Array arr(5);
    std::string textFilename = "empty_array.txt";
    std::string binaryFilename = "empty_array.bin";

    // Текстовая сериализация
    EXPECT_NO_THROW(arr.serializeToText(textFilename));

    Array textArray(5);
    EXPECT_NO_THROW(textArray.deserializeFromText(textFilename));
    EXPECT_EQ(textArray.length(), 0);

    // Бинарная сериализация
    EXPECT_NO_THROW(arr.serializeToBinary(binaryFilename));

    Array binaryArray(5);
    EXPECT_NO_THROW(binaryArray.deserializeFromBinary(binaryFilename));
    EXPECT_EQ(binaryArray.length(), 0);

    // Удаляем временные файлы
    std::remove(textFilename.c_str());
    std::remove(binaryFilename.c_str());
}

// Тест: Удаление элемента
TEST(ArrayTest, RemoveElement) {
    Array arr(5);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    arr.remove(1); // Удаляем элемент с индексом 1
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.get(0), 10);
    EXPECT_EQ(arr.get(1), 30);

    // Проверка удаления последнего элемента
    arr.remove(1);
    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.get(0), 10);

    // Проверка удаления первого элемента
    arr.remove(0);
    EXPECT_EQ(arr.length(), 0);

    // Проверка исключений
    EXPECT_THROW(arr.remove(0), std::out_of_range);
    EXPECT_THROW(arr.remove(-1), std::out_of_range);
    EXPECT_THROW(arr.remove(5), std::out_of_range);
}

// Тест: Замена элемента
TEST(ArrayTest, ReplaceElement) {
    Array arr(3);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    // Замена элемента
    arr.replace(1, 50); // Заменяем элемент с индексом 1
    EXPECT_EQ(arr.get(1), 50);

    arr.replace(0, 100); // Заменяем первый элемент
    EXPECT_EQ(arr.get(0), 100);

    arr.replace(2, 200); // Заменяем последний элемент
    EXPECT_EQ(arr.get(2), 200);

    // Проверка исключений
    EXPECT_THROW(arr.replace(-1, 0), std::out_of_range);
    EXPECT_THROW(arr.replace(3, 0), std::out_of_range);
}

// Тест: Получение длины массива
TEST(ArrayTest, GetLength) {
    Array arr(3);
    EXPECT_EQ(arr.length(), 0); // Проверяем длину пустого массива

    arr.append(10);
    EXPECT_EQ(arr.length(), 1);

    arr.append(20);
    arr.append(30);
    EXPECT_EQ(arr.length(), 3);

    arr.remove(2);
    EXPECT_EQ(arr.length(), 2);

    arr.remove(0);
    EXPECT_EQ(arr.length(), 1);

    arr.remove(0);
    EXPECT_EQ(arr.length(), 0);
}

// Тест: Вывод массива в консоль
TEST(ArrayTest, DisplayArray) {
    Array arr(3);
    arr.append(10);
    arr.append(20);
    arr.append(30);

    // Захват вывода в консоль
    testing::internal::CaptureStdout();
    arr.display();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "10 20 30 \n");

    // Проверка пустого массива
    arr.free(); // Очищаем массив
    testing::internal::CaptureStdout();
    arr.display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\n");
}