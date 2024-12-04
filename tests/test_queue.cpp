#include "../src/Queue.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>

using namespace std;

TEST(QueueTest, EnqueueDequeueTest) {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    ASSERT_EQ(q.dequeue(), 10);
    ASSERT_EQ(q.dequeue(), 20);
    ASSERT_EQ(q.dequeue(), 30);

    // Проверка исключения при попытке извлечь из пустой очереди
    ASSERT_THROW(q.dequeue(), std::underflow_error);
}

TEST(QueueTest, PrintTest) {
    Queue q;
    q.enqueue(5);
    q.enqueue(15);
    q.enqueue(25);

    // Захват вывода для проверки содержимого очереди
    testing::internal::CaptureStdout();
    q.print();
    string output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, "Очередь: 5 15 25 \n");
}

TEST(QueueTest, SerializeToTextTest) {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    q.serializeToText("queue.txt");

    // Проверяем содержимое файла
    ifstream file("queue.txt");
    ASSERT_TRUE(file.is_open());

    string line;
    vector<int> values;
    while (getline(file, line)) {
        values.push_back(stoi(line));
    }

    ASSERT_EQ(values.size(), 3);
    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 2);
    ASSERT_EQ(values[2], 3);

    file.close();
    remove("queue.txt");
}

TEST(QueueTest, DeserializeFromTextTest) {
    ofstream file("queue.txt");
    file << "10\n20\n30\n";
    file.close();

    Queue q;
    q.deserializeFromText("queue.txt");

    ASSERT_EQ(q.dequeue(), 10);
    ASSERT_EQ(q.dequeue(), 20);
    ASSERT_EQ(q.dequeue(), 30);

    ASSERT_THROW(q.dequeue(), std::underflow_error);

    remove("queue.txt");
}

TEST(QueueTest, SerializeToBinaryTest) {
    Queue q;
    q.enqueue(100);
    q.enqueue(200);
    q.enqueue(300);

    q.serializeToBinary("queue.bin");

    // Проверяем содержимое файла
    ifstream file("queue.bin", ios::binary);
    ASSERT_TRUE(file.is_open());

    vector<int> values;
    int value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        values.push_back(value);
    }

    ASSERT_EQ(values.size(), 3);
    ASSERT_EQ(values[0], 100);
    ASSERT_EQ(values[1], 200);
    ASSERT_EQ(values[2], 300);

    file.close();
    remove("queue.bin");
}

TEST(QueueTest, DeserializeFromBinaryTest) {
    ofstream file("queue.bin", ios::binary);
    int values[] = {10, 20, 30};
    file.write(reinterpret_cast<const char*>(values), sizeof(values));
    file.close();

    Queue q;
    q.deserializeFromBinary("queue.bin");

    ASSERT_EQ(q.dequeue(), 10);
    ASSERT_EQ(q.dequeue(), 20);
    ASSERT_EQ(q.dequeue(), 30);

    ASSERT_THROW(q.dequeue(), std::underflow_error);

    remove("queue.bin");
}

TEST(QueueTest, ClearTest) {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    q.clear();

    ASSERT_THROW(q.dequeue(), std::underflow_error);
}

