#include "../src/HashTable.h"
#include <gtest/gtest.h>
#include <fstream>

// Проверка вставки и получения значений
TEST(HashTableTest, InsertAndGet) {
    HashTable hash;

    hash.insert("key1", "value1");
    hash.insert("key2", "value2");
    hash.insert("key3", "value3");

    EXPECT_EQ(hash.get("key1"), "value1");
    EXPECT_EQ(hash.get("key2"), "value2");
    EXPECT_EQ(hash.get("key3"), "value3");
    EXPECT_EQ(hash.get("key4"), "Ключ не найден"); // Несуществующий ключ
}

// Проверка обновления существующего значения
TEST(HashTableTest, UpdateExistingKey) {
    HashTable hash;

    hash.insert("key1", "value1");
    hash.insert("key1", "updatedValue");

    EXPECT_EQ(hash.get("key1"), "updatedValue");
}

// Проверка удаления существующего ключа
TEST(HashTableTest, RemoveKey) {
    HashTable hash;

    hash.insert("key1", "value1");
    hash.insert("key2", "value2");

    hash.remove("key1");
    EXPECT_EQ(hash.get("key1"), "Ключ не найден");
    EXPECT_EQ(hash.get("key2"), "value2");
}

// Проверка удаления несуществующего ключа
TEST(HashTableTest, RemoveNonexistentKey) {
    HashTable hash;

    hash.insert("key1", "value1");
    hash.remove("key2"); // Удаление несуществующего ключа

    EXPECT_EQ(hash.get("key1"), "value1");
}

// Проверка очистки таблицы
TEST(HashTableTest, ClearTable) {
    HashTable hash;

    hash.insert("key1", "value1");
    hash.insert("key2", "value2");
    hash.clear();

    EXPECT_EQ(hash.get("key1"), "Ключ не найден");
    EXPECT_EQ(hash.get("key2"), "Ключ не найден");
}

// Проверка сериализации и десериализации в текстовый файл
TEST(HashTableTest, SerializeToTextAndDeserializeFromText) {
    HashTable hash;

    hash.insert("key1", "value1");
    hash.insert("key2", "value2");

    const std::string filename = "test_hash_table.txt";
    hash.serializeToText(filename);

    HashTable newHash;
    newHash.deserializeFromText(filename);

    EXPECT_EQ(newHash.get("key1"), "value1");
    EXPECT_EQ(newHash.get("key2"), "value2");

    std::remove(filename.c_str()); // Удаление тестового файла
}

// Проверка сериализации и десериализации в бинарный файл
TEST(HashTableTest, SerializeToBinaryAndDeserializeFromBinary) {
    HashTable hash;

    hash.insert("key1", "value1");
    hash.insert("key2", "value2");

    const std::string filename = "test_hash_table.bin";
    hash.serializeToBinary(filename);

    HashTable newHash;
    newHash.deserializeFromBinary(filename);

    EXPECT_EQ(newHash.get("key1"), "value1");
    EXPECT_EQ(newHash.get("key2"), "value2");

    std::remove(filename.c_str()); // Удаление тестового файла
}

// Проверка печати таблицы
TEST(HashTableTest, PrintTable) {
    HashTable hash;

    hash.insert("key1", "value1");
    hash.insert("key2", "value2");

    testing::internal::CaptureStdout();
    hash.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);
    EXPECT_NE(output.find("key2"), std::string::npos);
    EXPECT_NE(output.find("value2"), std::string::npos);
}

// Проверка пустой таблицы
TEST(HashTableTest, EmptyTable) {
    HashTable hash;

    EXPECT_EQ(hash.get("key1"), "Ключ не найден");

    testing::internal::CaptureStdout();
    hash.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Index") != std::string::npos); // Печать структуры таблицы
}
