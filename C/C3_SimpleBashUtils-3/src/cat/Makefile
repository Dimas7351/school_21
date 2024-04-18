CFLAGS = -Wall -Werror -Wextra

all: s21_cat clang

s21_cat: clang
	gcc $(CFLAGS) s21_cat.c -o s21_cat

clang:
	clang-format -i s21_cat.c
	clang-format -i s21_cat.h

clean:
	rm s21_cat
