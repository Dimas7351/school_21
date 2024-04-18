
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LDFLAGS=$(shell pkg-config --cflags --libs check)
TEST_LIBS = -lcheck -lm -lpthread
GCOVFLAGS=-fprofile-arcs -ftest-coverage

all: s21_matrix.a


s21_matrix.a: 
	$(CC) $(CFLAGS) -c s21_matrix.c
	ar r s21_matrix.a *.o
	ranlib s21_matrix.a


test: matrix_test.c s21_matrix.a
	$(CC)  $(CFLAGS)  s21_matrix.c matrix_test.c $(LDFLAGS) -o  test
	./test
	

gcov_report: matrix_test.c	s21_matrix.c
	clear
	$(CC) $(CFLAGS) --coverage s21_matrix.c matrix_test.c $(LDFLAGS)  -o coverage 
	./coverage
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o gcov_report
	

clean:
	rm -rf *.o *.out *.a *.cfg *.html *.css *.a
	rm -rf *.gcda *.gcno *.info *.txt 
	rm -rf coverage gcov_report test

	