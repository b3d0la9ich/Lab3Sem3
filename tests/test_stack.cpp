#include "../src/Stack.h"
#include "gtest/gtest.h"
#include <fstream>
#include <sstream>
#include <string>

TEST(StackTest, PushAndPop) {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    stack.print();
    output.str(testing::internal::GetCapturedStdout());

    EXPECT_EQ(output.str(), "Элементы стека: 30 20 10 \n");

    stack.pop();
    testing::internal::CaptureStdout();
    stack.print();
    output.str(testing::internal::GetCapturedStdout());

    EXPECT_EQ(output.str(), "Элементы стека: 20 10 \n");
}

TEST(StackTest, SerializeToText) {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::string filename = "stack_text.txt";
    stack.serializeToText(filename);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string content;
    std::getline(file, content);
    EXPECT_EQ(content, "30");

    std::getline(file, content);
    EXPECT_EQ(content, "20");

    std::getline(file, content);
    EXPECT_EQ(content, "10");

    file.close();
    std::remove(filename.c_str());
}

TEST(StackTest, DeserializeFromText) {
    Stack stack;

    std::string filename = "stack_text.txt";
    std::ofstream file(filename);
    file << "30\n20\n10\n";
    file.close();

    stack.deserializeFromText(filename);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    stack.print();
    output.str(testing::internal::GetCapturedStdout());

    EXPECT_EQ(output.str(), "Элементы стека: 10 20 30 \n");

    std::remove(filename.c_str());
}

TEST(StackTest, SerializeToBinary) {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::string filename = "stack_binary.bin";
    stack.serializeToBinary(filename);

    std::ifstream file(filename, std::ios::binary);
    ASSERT_TRUE(file.is_open());

    int value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    EXPECT_EQ(value, 30);

    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    EXPECT_EQ(value, 20);

    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    EXPECT_EQ(value, 10);

    file.close();
    std::remove(filename.c_str());
}

TEST(StackTest, DeserializeFromBinary) {
    Stack stack;

    std::string filename = "stack_binary.bin";
    std::ofstream file(filename, std::ios::binary);
    int values[] = {30, 20, 10};
    for (int value : values) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    file.close();

    stack.deserializeFromBinary(filename);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    stack.print();
    output.str(testing::internal::GetCapturedStdout());

    EXPECT_EQ(output.str(), "Элементы стека: 10 20 30 \n");

    std::remove(filename.c_str());
}


TEST(StackTest, PrintEmptyStack) {
    Stack stack;

    testing::internal::CaptureStdout(); // Перехватываем вывод в консоль
    stack.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Стек пуст\n"); // Проверяем, что сообщение соответствует
}

