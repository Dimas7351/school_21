CC=gcc
CFLAGS=-Wall	-Wextra	-Werror	-std=c11
COVFLAGS=-fprofile-arcs	-ftest-coverage

OS=$(shell uname)
ifeq ($(OS), Darwin)
	PKGFLAGS=-lcheck
else
	CHECKFLAGS=-lcheck	-lpthread	-lpthread	-lrt	-lm	-lsubunit
endif

all: clean s21_string.a

test:
	checkmk clean_mode=1 my.check > s21_string_test.c
	$(CC)	s21_string_test.c	s21_string.c	s21_sscanf.c	s21_sprintf.c	$(PKGFLAGS)	-o	s21_string_test $(CHECKFLAGS)	--coverage
	./s21_string_test

s21_string.a: clean
	$(CC)	$(CFLAGS)	-c	s21_string.c s21_sprintf.c s21_sscanf.c
	ar rc	s21_string.a	*.o
	ranlib s21_string.a

gcov_report:	clean	s21_string.a test
	./s21_string_test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	rm -rf	*.gcno	*.gcda gcov_rep gcov_rep.* coverage.info
	chmod -x *.* Makefile
	open gcov_report/index.html

clean:
	rm -rf *.a *.o report/ s21_string_test *.out *.gcda *.gcno *.dSYM gcov_* *.*.gch s21_string_test.c	coverage.info

clean_test_temps:
	rm -rf s21_string_test*.* core*	

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -i *.c
