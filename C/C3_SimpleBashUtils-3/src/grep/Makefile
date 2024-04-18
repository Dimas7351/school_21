CFLAGS = -Wall -Werror -Wextra

all: s21_grep clang

s21_grep: clang
	gcc $(CFLAGS) s21_grep.c -o s21_grep

clang:
	clang-format -i s21_grep.c
	clang-format -i s21_grep.h

clean:
	rm s21_grep
	