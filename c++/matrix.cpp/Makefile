.PHONY: all clean

CC=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
LDFLAGS=$(shell pkg-config --cflags --libs gtest)
NFLAGS=-lgtest

all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) $(FLAGS) -c s21_matrix_oop.cpp
	ar rc s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a

test: clean
	$(CC) $(FLAGS) *.cpp $(LDFLAGS)
	./a.out

clean:
	rm -f *.o *.a *.out
