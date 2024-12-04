#include <gtest/gtest.h>
#include "../src/HashTable.h"
#include "../src/LO.h"
#include "../src/LS.h"
#include "../src/Array.h"
#include "../src/Queue.h"
#include "../src/Stack.h"
#include "../src/AVL.h"
#include <sstream>

// Тесты для HashTable
TEST(MainTest, HashtableCommands) {
    HashTable hashTable;

    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");
    EXPECT_EQ(hashTable.get("key1"), "value1");
    EXPECT_EQ(hashTable.get("key2"), "value2");

    hashTable.remove("key1");
    EXPECT_EQ(hashTable.get("key1"), "Ключ не найден");

    std::ostringstream output;
    testing::internal::CaptureStdout();
    hashTable.print();
    output << testing::internal::GetCapturedStdout();
    EXPECT_NE(output.str().find("[key2: value2]"), std::string::npos);
}

// Тесты для ListOne
TEST(MainTest, ListOneCommands) {
    ListOne list;

    list.addToHead(10);
    list.addToHead(20);
    EXPECT_TRUE(list.search(10));
    EXPECT_TRUE(list.search(20));

    list.addToTail(30);
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.print();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "20 10 30 \n");

    list.removeByValue(10);
    EXPECT_FALSE(list.search(10));

    list.removeHead();
    EXPECT_FALSE(list.search(20));
}

// Тесты для DoubleList
TEST(MainTest, ListTwoCommands) {
    DoubleList list;

    list.addToHead(10);
    list.addToHead(20);
    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(20));

    list.addToTail(30);
    std::ostringstream output;
    testing::internal::CaptureStdout();
    list.print();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "20 10 30 \n");

    list.removeFromHead();
    EXPECT_FALSE(list.find(20));
}

// Тесты для Array
TEST(MainTest, ArrayCommands) {
    Array array(5);

    array.append(10);
    array.append(20);
    array.append(30);
    EXPECT_EQ(array.get(0), 10);
    EXPECT_EQ(array.get(1), 20);
    EXPECT_EQ(array.get(2), 30);

    array.insert(1, 15);
    EXPECT_EQ(array.get(1), 15);

    array.remove(2);
    EXPECT_EQ(array.get(2), 30);

    array.replace(0, 5);
    EXPECT_EQ(array.get(0), 5);
}

// Тесты для Queue
TEST(MainTest, QueueCommands) {
    Queue queue;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    queue.print();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "Очередь: 10 20 30 \n");

    EXPECT_EQ(queue.dequeue(), 10);
    EXPECT_EQ(queue.dequeue(), 20);
    EXPECT_EQ(queue.dequeue(), 30);
}

// Тесты для Stack
TEST(MainTest, StackCommands) {
    Stack stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::ostringstream output;
    testing::internal::CaptureStdout();
    stack.print();
    output << testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.str(), "Элементы стека: 30 20 10 \n");

    stack.pop();
    EXPECT_NO_THROW(stack.pop());
    EXPECT_NO_THROW(stack.pop());
}

// Тесты для AVLTree
TEST(MainTest, AVLTreeCommands) {
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(15);

    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(15));

    tree.remove(20);
    EXPECT_FALSE(tree.search(20));

    std::ostringstream output;
    testing::internal::CaptureStdout();
    tree.print();
    output << testing::internal::GetCapturedStdout();
    EXPECT_NE(output.str().find("15"), std::string::npos);
}

// Основная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
