cmake_minimum_required(VERSION 3.10)

# Имя проекта
project(Lab3Sem3)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Пути к исходникам
set(SRC_FILES
    src/Queue.cpp
    src/Stack.cpp
    src/ListOne.cpp
    src/ListSecond.cpp
    src/HashTable.cpp
    src/AVL.cpp
    src/Array.cpp
)

# Тестовые файлы
set(TEST_FILES
    tests/test_queue.cpp
    tests/test_stack.cpp
    tests/test_LS.cpp 
    tests/test_LO.cpp 
    tests/test_HashTable.cpp 
    tests/test_AVL.cpp 
    tests/test_array.cpp
)

# Добавляем Google Test
add_subdirectory(googletest)

# Добавляем путь к заголовочным файлам
include_directories(${CMAKE_SOURCE_DIR}/src)

# Главный исполняемый файл для проекта (если есть основная программа)
add_executable(main_program src/main.cpp ${SRC_FILES})

# Таргет для тестов
add_executable(tests ${TEST_FILES})
target_link_libraries(tests gtest gtest_main pthread)

# Линкуем исходные файлы только для тестов
target_sources(tests PRIVATE ${SRC_FILES})
