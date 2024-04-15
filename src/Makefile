CC= g++
TEST= *.cc
TEST_FLAGS = -lgtest -lgtest_main
CFLAGS = -Wall -Wextra -Werror -std=c++17
OS := $(shell uname -s)

all: clean s21_matrix_oop.a test

test: clean
		$(CC) $(TEST_FLAGS) $(CFLAGS) $(TEST) -o test
		./test

clean:
		rm -rf test
		rm -rf *.a *.out *.o report *.gc* s21_matrix_oop.a *.info

s21_matrix_oop.a: clean
		$(CC) $(CFLAGS) s21_*.cc -c 
		ar rcs s21_matrix_oop.a *.o

rebuild:
		make clean
		make all

leak:
		CK_FORK=no leaks --atExit -- ./test 

linter:
		cp ../materials/linters/.clang-format ..
		clang-format -n *.cc *.h
		rm -rf ../.clang-format

gcov_report: clean
		$(CC) --coverage $(TEST_FLAGS) $(CFLAGS) $(TEST) -o test
		./test
		lcov -t "test" -o test.info -c -d . 
		genhtml -o report test.info
		open report/index.html

style:
		cp ../materials/linters/.clang-format ..
		clang-format -i *.cc *.h
		rm -rf ../.clang-format