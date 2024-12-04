#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "HashTable.h"
#include "LO.h"
#include "LS.h"
#include "Array.h"
#include "Queue.h"
#include "Stack.h"
#include "AVL.h"

using namespace std;

void arrayCmds(Array& arr) {
    string command;
    int index, value;

    cout << "Введите команду (APPEND, INSERT, REMOVE, REPLACE, GET, DISPLAY, LENGTH, WRITETEXT, READTEXT, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "APPEND") {
            ss >> value;
            if (!ss.fail()) {
                try {
                    arr.append(value);
                    cout << "Элемент " << value << " добавлен в конец массива." << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                cout << "> Неверный ввод. Необходимо ввести: APPEND <значение>" << endl;
            }
        } 
        else if (action == "INSERT") {
            ss >> index >> value;
            if (!ss.fail()) {
                try {
                    arr.insert(index, value);
                    cout << "Элемент " << value << " вставлен в массив на позицию " << index << "." << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                cout << "> Неверный ввод. Необходимо ввести: INSERT <индекс> <значение>" << endl;
            }
        } 
        else if (action == "REMOVE") {
            ss >> index;
            if (!ss.fail()) {
                try {
                    arr.remove(index);
                    cout << "Элемент на позиции " << index << " удален." << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVE <индекс>" << endl;
            }
        } 
        else if (action == "REPLACE") {
            ss >> index >> value;
            if (!ss.fail()) {
                try {
                    arr.replace(index, value);
                    cout << "Элемент на позиции " << index << " заменен на " << value << "." << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                cout << "> Неверный ввод. Необходимо ввести: REPLACE <индекс> <значение>" << endl;
            }
        } 
        else if (action == "GET") {
            ss >> index;
            if (!ss.fail()) {
                try {
                    int result = arr.get(index);
                    cout << "Элемент на позиции " << index << ": " << result << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                cout << "> Неверный ввод. Необходимо ввести: GET <индекс>" << endl;
            }
        } 
        else if (action == "DISPLAY") {
            cout << "Содержимое массива: ";
            arr.display();
        } 
        else if (action == "LENGTH") {
            cout << "Длина массива: " << arr.length() << endl;
        } 
        else if (action == "WRITETEXT") {
            try {
                arr.writeToFile("array.txt");
                cout << "Массив успешно сохранен в файл array.txt." << endl;
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "READTEXT") {
            try {
                Array temp(arr.length()); // Создаем временный массив для чтения
                ifstream file("array.txt");
                int value;
                while (file >> value) {
                    temp.append(value);
                }
                arr = move(temp); // Замещаем текущий массив
                cout << "Массив успешно загружен из файла array.txt." << endl;
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допустимые команды: APPEND, INSERT, REMOVE, REPLACE, GET, DISPLAY, LENGTH, WRITETEXT, READTEXT, EXIT." << endl;
        }
    }
}

void queueCmds(Queue& q) {
    string command;
    int value;

    cout << "Введите команду (ENQUEUE, DEQUEUE, PRINT, SERIALIZETEXT, DESERIALIZETEXT, SERIALIZEBIN, DESERIALIZEBIN, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ENQUEUE") {
            ss >> value;
            if (!ss.fail()) {
                q.enqueue(value);
                cout << "Элемент " << value << " добавлен в очередь." << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: ENQUEUE <значение>" << endl;
            }
        } 
        else if (action == "DEQUEUE") {
            try {
                int result = q.dequeue();
                cout << "Элемент " << result << " удален из очереди." << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        } 
        else if (action == "PRINT") {
            q.print();
        }
        else if (action == "SERIALIZETEXT") {
            try {
                q.serializeToText("queue.txt");
                cout << "Очередь успешно сохранена в текстовый файл queue.txt" << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "DESERIALIZETEXT") {
            try {
                q.deserializeFromText("queue.txt");
                cout << "Очередь успешно загружена из текстового файла queue.txt" << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "SERIALIZEBIN") {
            try {
                q.serializeToBinary("queue.bin");
                cout << "Очередь успешно сохранена в бинарный файл queue.bin" << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "DESERIALIZEBIN") {
            try {
                q.deserializeFromBinary("queue.bin");
                cout << "Очередь успешно загружена из бинарного файла queue.bin" << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допустимые команды: ENQUEUE, DEQUEUE, PRINT, SERIALIZETEXT, DESERIALIZETEXT, SERIALIZEBIN, DESERIALIZEBIN, EXIT." << endl;
        }
    }
}

void stackCmds(Stack& stack) {
    string command;
    int value;

    cout << "Введите команду (PUSH, POP, PRINT, SERIALIZETEXT, DESERIALIZETEXT, SERIALIZEBIN, DESERIALIZEBIN, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "PUSH") {
            ss >> value;
            if (!ss.fail()) {
                stack.push(value);
                cout << "Элемент " << value << " добавлен в стек." << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: PUSH <значение>" << endl;
            }
        } 
        else if (action == "POP") {
            try {
                stack.pop();
                cout << "Элемент удален с вершины стека." << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        } 
        else if (action == "PRINT") {
            stack.print();
        } 
        else if (action == "SERIALIZETEXT") {
            try {
                stack.serializeToText("stack.txt");
                cout << "Стек успешно сохранен в текстовый файл stack.txt" << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "DESERIALIZETEXT") {
            try {
                stack.deserializeFromText("stack.txt");
                cout << "Стек успешно загружен из текстового файла stack.txt" << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "SERIALIZEBIN") {
            try {
                stack.serializeToBinary("stack.bin");
                cout << "Стек успешно сохранен в бинарный файл stack.bin" << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "DESERIALIZEBIN") {
            try {
                stack.deserializeFromBinary("stack.bin");
                cout << "Стек успешно загружен из бинарного файла stack.bin" << endl;
            } catch (const std::exception& e) {
                cout << e.what() << endl;
            }
        }
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допустимые команды: PUSH, POP, PRINT, SERIALIZETEXT, DESERIALIZETEXT, SERIALIZEBIN, DESERIALIZEBIN, EXIT." << endl;
        }
    }
}

void hashtableCmds(HashTable& hashTable) {
    std::string command;
    std::string key, value;

    std::cout << "Введите команду (INSERT, GET, REMOVE, PRINT, SAVE_TEXT, LOAD_TEXT, SAVE_BINARY, LOAD_BINARY, EXIT):" << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        std::stringstream ss(command);
        std::string action;
        ss >> action;

        if (action == "INSERT") {
            if (ss >> key >> value && !key.empty() && !value.empty()) {
                hashTable.insert(key, value);
                std::cout << "Ключ и значение успешно добавлены!" << std::endl;
            } else {
                std::cout << "> Неверный ввод. Необходимо ввести: INSERT <ключ> <значение>" << std::endl;
            }
        } else if (action == "GET") {
            if (ss >> key && !key.empty()) {
                std::cout << "Значение: " << hashTable.get(key) << std::endl;
            } else {
                std::cout << "> Неверный ввод. Необходимо ввести: GET <ключ>" << std::endl;
            }
        } else if (action == "REMOVE") {
            if (ss >> key && !key.empty()) {
                hashTable.remove(key);
                std::cout << "Ключ успешно удален!" << std::endl;
            } else {
                std::cout << "> Неверный ввод. Необходимо ввести: REMOVE <ключ>" << std::endl;
            }
        } else if (action == "PRINT") {
            hashTable.print();
        } else if (action == "SAVE_TEXT") {
            std::string filename;
            ss >> filename;
            if (!filename.empty()) {
                try {
                    hashTable.serializeToText(filename);
                    std::cout << "Данные успешно сохранены в текстовый файл: " << filename << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка сохранения в файл: " << e.what() << std::endl;
                }
            } else {
                std::cout << "> Неверный ввод. Необходимо ввести: SAVE_TEXT <имя_файла>" << std::endl;
            }
        } else if (action == "LOAD_TEXT") {
            std::string filename;
            ss >> filename;
            if (!filename.empty()) {
                try {
                    hashTable.deserializeFromText(filename);
                    std::cout << "Данные успешно загружены из текстового файла: " << filename << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка загрузки из файла: " << e.what() << std::endl;
                }
            } else {
                std::cout << "> Неверный ввод. Необходимо ввести: LOAD_TEXT <имя_файла>" << std::endl;
            }
        } else if (action == "SAVE_BINARY") {
            std::string filename;
            ss >> filename;
            if (!filename.empty()) {
                try {
                    hashTable.serializeToBinary(filename);
                    std::cout << "Данные успешно сохранены в бинарный файл: " << filename << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка сохранения в файл: " << e.what() << std::endl;
                }
            } else {
                std::cout << "> Неверный ввод. Необходимо ввести: SAVE_BINARY <имя_файла>" << std::endl;
            }
        } else if (action == "LOAD_BINARY") {
            std::string filename;
            ss >> filename;
            if (!filename.empty()) {
                try {
                    hashTable.deserializeFromBinary(filename);
                    std::cout << "Данные успешно загружены из бинарного файла: " << filename << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Ошибка загрузки из файла: " << e.what() << std::endl;
                }
            } else {
                std::cout << "> Неверный ввод. Необходимо ввести: LOAD_BINARY <имя_файла>" << std::endl;
            }
        } else if (action == "EXIT") {
            break;
        } else {
            std::cout << "> Неизвестная команда. Допустимые команды: INSERT, GET, REMOVE, PRINT, SAVE_TEXT, LOAD_TEXT, SAVE_BINARY, LOAD_BINARY, EXIT." << std::endl;
        }
    }
}

void treeCmds(AVLTree& tree) {
    string command;
    int value;

    cout << "Введите команду (INSERT, DELETE, SEARCH, PRINT, SAVE_TEXT, LOAD_TEXT, SAVE_BINARY, LOAD_BINARY, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "INSERT") {
            ss >> value;
            if (!ss.fail()) {
                tree.insert(value);
                cout << "Значение " << value << " добавлено в дерево." << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: INSERT <значение>" << endl;
            }
        } else if (action == "DELETE") {
            ss >> value;
            if (!ss.fail()) {
                tree.remove(value);
                cout << "Значение " << value << " удалено из дерева." << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: DELETE <значение>" << endl;
            }
        } else if (action == "SEARCH") {
            if (ss >> value) {
                bool result = tree.search(value);
                cout << "Результат поиска для значения " << value << ": "
                     << (result ? "Найдено" : "Не найдено") << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: SEARCH <значение>" << endl;
            }
        } else if (action == "PRINT") {
            cout << "Текущее дерево:" << endl;
            tree.print();
            cout << endl;
        } else if (action == "SAVE_TEXT") {
            tree.serializeToText("tree.txt");
            cout << "Дерево сохранено в текстовый файл tree.txt." << endl;
        } else if (action == "LOAD_TEXT") {
            tree.deserializeFromText("tree.txt");
            cout << "Дерево загружено из текстового файла tree.txt." << endl;
        } else if (action == "SAVE_BINARY") {
            tree.serializeToBinary("tree.bin");
            cout << "Дерево сохранено в бинарный файл tree.bin." << endl;
        } else if (action == "LOAD_BINARY") {
            tree.deserializeFromBinary("tree.bin");
            cout << "Дерево загружено из бинарного файла tree.bin." << endl;
        } else if (action == "EXIT") {
            break;
        } else {
            cout << "> Неизвестная команда. Допустимые команды: INSERT, DELETE, SEARCH, PRINT, SAVE_TEXT, LOAD_TEXT, SAVE_BINARY, LOAD_BINARY, EXIT." << endl;
        }
    }
}

void list1Cmds(ListOne& listone) {
    string command;
    int value;

    cout << "Введите команду (ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, SEARCH, PRINT, LOADTEXT, LOADBINARY, SAVETEXT, SAVEBINARY, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ADDHEAD") {
            ss >> value;
            if (!ss.fail()) {
                listone.addToHead(value);
            } else {
                cout << "> Неверный ввод. Необходимо ввести: ADDHEAD <значение>" << endl;
            }
        } 
        else if (action == "ADDTAIL") {
            ss >> value;
            if (!ss.fail()) {
                listone.addToTail(value);
            } else {
                cout << "> Неверный ввод. Необходимо ввести: ADDTAIL <значение>" << endl;
            }
        } 
        else if (action == "REMOVEHEAD") {
            listone.removeHead();
        } 
        else if (action == "REMOVETAIL") {
            listone.removeTail();
        } 
        else if (action == "REMOVEVALUE") {
            ss >> value;
            if (!ss.fail()) {
                listone.removeByValue(value);
            } else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEVALUE <значение>" << endl;
            }
        } 
        else if (action == "SEARCH") {
            ss >> value;
            if (!ss.fail()) {
                cout << "Результат поиска для значения " << value << ": " 
                     << (listone.search(value) ? "Найдено" : "Не найдено") << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: SEARCH <значение>" << endl;
            }
        } 
        else if (action == "PRINT") {
            cout << "Содержимое списка: ";
            listone.print();
        } 
        else if (action == "LOADTEXT") {
            try {
                listone.deserializeFromText("list1.txt");
                cout << "> Список загружен из текстового файла." << endl;
            } catch (const runtime_error& e) {
                cout << "> Ошибка: " << e.what() << endl;
            }
        }
        else if (action == "LOADBINARY") {
            try {
                listone.deserializeFromBinary("list1.bin");
                cout << "> Список загружен из бинарного файла." << endl;
            } catch (const runtime_error& e) {
                cout << "> Ошибка: " << e.what() << endl;
            }
        }
        else if (action == "SAVETEXT") {
            try {
                listone.serializeToText("list1.txt");
                cout << "> Список сохранен в текстовый файл." << endl;
            } catch (const runtime_error& e) {
                cout << "> Ошибка: " << e.what() << endl;
            }
        }
        else if (action == "SAVEBINARY") {
            try {
                listone.serializeToBinary("list1.bin");
                cout << "> Список сохранен в бинарный файл." << endl;
            } catch (const runtime_error& e) {
                cout << "> Ошибка: " << e.what() << endl;
            }
        }
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допустимые команды: ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, SEARCH, PRINT, LOADTEXT, LOADBINARY, SAVETEXT, SAVEBINARY, EXIT." << endl;
        }
    }
}

void list2Cmds(DoubleList& list) {
    string command;
    int value;

    cout << "Введите команду (ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, FIND, PRINT, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "ADDHEAD") {
            ss >> value;
            if (!ss.fail()) {
                list.addToHead(value);
                list.serializeToText("list2.txt");
            } else {
                cout << "> Неверный ввод. Необходимо ввести: ADDHEAD <значение>" << endl;
            }
        } 
        else if (action == "ADDTAIL") {
            ss >> value;
            if (!ss.fail()) {
                list.addToTail(value);
                list.serializeToText("list2.txt");
            } else {
                cout << "> Неверный ввод. Необходимо ввести: ADDTAIL <значение>" << endl;
            }
        } 
        else if (action == "REMOVEHEAD") {
            list.removeFromHead();
            list.serializeToText("list2.txt");
        } 
        else if (action == "REMOVETAIL") {
            list.removeFromTail();
            list.serializeToText("list2.txt");
        } 
        else if (action == "REMOVEVALUE") {
            ss >> value;
            if (!ss.fail()) {
                list.removeByValue(value);
                list.serializeToText("list2.txt");
            } else {
                cout << "> Неверный ввод. Необходимо ввести: REMOVEVALUE <значение>" << endl;
            }
        } 
        else if (action == "FIND") {
            ss >> value;
            if (!ss.fail()) {
                bool result = list.find(value);
                cout << "Результат поиска для значения " << value << ": " 
                     << (result ? "Найдено" : "Не найдено") << endl;
            } else {
                cout << "> Неверный ввод. Необходимо ввести: FIND <значение>" << endl;
            }
        } 
        else if (action == "PRINT") {
            cout << "Содержимое списка: ";
            list.print();
        } 
        else if (action == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Допустимые команды: ADDHEAD, ADDTAIL, REMOVEHEAD, REMOVETAIL, REMOVEVALUE, FIND, PRINT, EXIT." << endl;
        }
    }
}

int main() {
    HashTable hashTable;
    ListOne listone;
    DoubleList list;
    Array arr;
    Queue q;
    Stack stack;
    AVLTree tree;

    string command;

    cout << "> Выберите структуру данных (HASHTABLE, LIST1, LIST2, ARRAY, QUEUE, STACK, AVLTREE, EXIT):" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command == "HASHTABLE") {
            hashtableCmds(hashTable);
        } 
        else if (command == "LIST1") {
            list1Cmds(listone);
        } 
        else if (command == "LIST2") {
            list2Cmds(list);
        } 
        else if (command == "ARRAY") {
            arrayCmds(arr);
        } 
        else if (command == "QUEUE") {
            queueCmds(q);
        } 
        else if (command == "STACK") {
            stackCmds(stack);
        } 
        else if (command == "AVLTREE") {
            treeCmds(tree);
        } 
        else if (command == "EXIT") {
            break;
        } 
        else {
            cout << "> Неизвестная команда. Доступные команды: HASHTABLE, LIST1, LIST2, ARRAY, QUEUE, STACK, AVLTREE, EXIT." << endl;
        }
    }

    hashTable.clear();
    listone.clear();
    list.clear();
    q.clear();
    stack.clear();
    tree.clear();

    return 0;
}