cmake_minimum_required(VERSION 3.16)

project(Lab3Sem3 LANGUAGES CXX)

# --- Компилятор и стандарт
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Исходники
set(SRC_FILES
    src/Queue.cpp
    src/Stack.cpp
    src/ListOne.cpp
    src/ListSecond.cpp
    src/HashTable.cpp
    src/AVL.cpp
    src/Array.cpp
)

set(TEST_FILES
    tests/test_queue.cpp
    tests/test_stack.cpp
    tests/test_LS.cpp
    tests/test_LO.cpp
    tests/test_HashTable.cpp
    tests/test_AVL.cpp
    tests/test_array.cpp
    tests/test_main.cpp    # если у тебя есть общий main для тестов — оставь; если нет, можешь убрать
)

# --- Пути заголовков
include_directories(${CMAKE_SOURCE_DIR}/src)

# --- Основная программа
add_executable(main_program src/main.cpp ${SRC_FILES})

# --- GoogleTest через FetchContent
include(FetchContent)
# Для MSVC: использовать общий CRT
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# --- Тесты
enable_testing()

add_executable(tests ${TEST_FILES})
target_sources(tests PRIVATE ${SRC_FILES})
target_link_libraries(tests
  PRIVATE
    GTest::gtest
    GTest::gtest_main
)

# pthread для Unix-платформ
if(UNIX AND NOT APPLE)
  target_link_libraries(tests PRIVATE pthread)
endif()

# Автоматическая регистрация тестов для ctest
include(GoogleTest)
gtest_discover_tests(tests)
