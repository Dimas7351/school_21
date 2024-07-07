#ifndef _SRC_S21_STRING_H_
#define _SRC_S21_STRING_H_

#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#include "s21_errors.h"
typedef long unsigned s21_size_t;
#define S21_NULL ((void *)0)
#define BUFF_SIZE 4096

//taken from en.cppreference.com/w/cpp/types/climits
#define MAX_INT   2147483647
#define MAX_LLONG 9223372036854775807LL
#define MAX_ULONG 18446744073709551615ULL
#define TOL 0.000001


int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
void *s21_memchr(const void *str, int c, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
s21_size_t s21_strcspn(const char *str1, const char *str2);
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strspn(const char *str1, const char *str2);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

char *trim_reverse(const char *src);

int s21_sscanf(const char *str, const char *format, ...);
int s21_sprintf(char *str, const char *format, ...);

bool isBasedDigit(char c, int b);
long long s21_atoi(char *sptr);

#endif  //_SRC_S21_STRING_H_