# Компилятор и флаги
CC = g++
CFLAGS = -std=c++17 -Wall -g --coverage
LDFLAGS = --coverage -lgtest -lgtest_main -lpthread

# Исходные файлы
SRC = src/Queue.cpp src/Stack.cpp src/Array.cpp src/HashTable.cpp src/AVL.cpp src/ListOne.cpp src/ListSecond.cpp
TEST_SRC = tests/test_queue.cpp tests/test_stack.cpp tests/test_array.cpp  tests/test_HashTable.cpp tests/test_AVL.cpp tests/test_LO.cpp tests/test_LS.cpp
# Цели сборки
all: test coverage

test: $(SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) -o test $(SRC) $(TEST_SRC) $(LDFLAGS)
	./test

coverage: test
	lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch
	lcov --remove coverage.info '/usr/*' --output-file coverage.filtered.info
	genhtml coverage.filtered.info --output-directory coverage_html
	@echo "HTML report generated in coverage_html/index.html"

clean:
	rm -f test *.gcno *.gcda *.info
	rm -rf coverage_html
