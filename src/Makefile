CC=g++
CC_FLAGS=-c -std=c++17 -pedantic -Wall -Werror -Wextra
TEST_FLAGS=-lgtest -lsubunit -lrt -lm -lpthread

all: s21_matrix_oop.a test gcov_report

s21_matrix_oop.a: s21_matrix_oop.o  util.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o util.o
	ranlib s21_matrix_oop.a

s21_matrix_oop.o: s21_matrix_oop.cpp
	${CC} ${CC_FLAGS} s21_matrix_oop.cpp -o s21_matrix_oop.o

util.o: util.cpp
	${CC} ${CC_FLAGS} util.cpp -o util.o

test: util.o s21_matrix_oop.o tests/tests.o tests/generated.o
	${CC} $^ ${TEST_FLAGS} -o tests/tests
	./tests/tests --gtest_brief=1

gcov_report: util.cpp s21_matrix_oop.cpp tests/tests.cpp tests/generated.cpp
	${CC} -std=c++17 --coverage $^ ${TEST_FLAGS} -o tests/test_report
	./tests/test_report --gtest_brief=1
	lcov --directory . --capture -o coverage.info
	genhtml --output-directory report --legend coverage.info
	-rm ./tests/*.gcda
	-rm ./tests/*.gcno
	-rm coverage.info

clean:
	-rm *.o
	-rm tests/*.o
	-rm s21_matrix_oop.a
	-rm tests/tests
	-rm tests/test_report
	-rm -r report