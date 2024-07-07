#include "s21_string.h"

// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  if (str1 != str2) {
    for (s21_size_t i = 0; i < n; i++) {
      if (*(char *)(str1 + i) != *(char *)(str2 + i)) {
        res = *(char *)(str1 + i) - *(char *)(str2 + i);
        break;
      }
    }
  }
  return res;
}

// Сравнивает строку, на которую указывает str1, со строкой, на которую
// указывает str2.
int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;
  if (str1 != str2) {
    while ((*str1 != '\0') && (*str1 - *str2 == 0)) {
      str1++;
      str2++;
    }
    res = *str1 - *str2;
  }
  return res;
}

// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  if (str1 != str2 && n != 0) {
    for (s21_size_t iterator = 0; iterator < n && res == 0; iterator++) {
      res = *(str1 + iterator) - *(str2 + iterator);
    }
  }
  return res;
}

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *res = S21_NULL;
  if (str != S21_NULL || n != 0) {
    int flag = 0;
    char *temp_str = (char *)str;
    s21_size_t iterator = 0;
    for (iterator = 0; iterator < n; iterator++) {
      if (temp_str[iterator] == c) {
        flag = 1;
        break;
      }
    }
    if (flag == 1) {
      res = temp_str + iterator;
    }
  }
  return res;
}
// Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  void *res = dest;
  if (n != 0 && dest != src) {
    char *temp_dest = (char *)dest;
    const char *temp_src = (const char *)src;
    if (temp_dest != S21_NULL && temp_src != 0) {
      for (s21_size_t iterator = 0; iterator < n; iterator++) {
        *temp_dest++ = *temp_src++;
      }
    }
  }
  return res;
}
// Еще одна функция для копирования n символов из src в dest.
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  void *res = dest;
  if (dest != src && n != 0) {
    char *temp_src = (char *)src;
    char *temp_dest = (char *)dest;
    for (s21_size_t iterator = 0; iterator < n; iterator++) {
      temp_dest[iterator] = temp_src[iterator];
    }
  }
  return res;
}
// Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
// указывает аргумент str.
void *s21_memset(void *str, int c, s21_size_t n) {
  void *res = str;
  if (str) {
    char *temp = (char *)str;
    while (n--) {
      *temp++ = c;
    }
  }
  return res;
}
// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest.
char *s21_strcat(char *dest, const char *src) {
  char *res = dest;
  while (*dest != '\0') {
    dest++;
  }
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  return res;
}

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *res = dest;
  if (dest != S21_NULL && src != S21_NULL) {
    while (*dest != '\0') {
      dest++;
    }
    for (s21_size_t iterator = 0; iterator < n; iterator++) {
      *dest = src[iterator];
      dest++;
    }
  }
  return res;
}

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
  char *res;
  int flag = 0;
  s21_size_t iterator = 0;
  while (1) {
    if (str[iterator] == (char)c ||
        (str[iterator] == '\0' && (char)c == '\0')) {
      flag = 1;
      break;
    } else if (str[iterator] == '\0') {
      break;
    }
    iterator++;
  }
  if (flag == 0) {
    res = S21_NULL;
  } else {
    res = (char *)str + iterator;
  }
  return res;
}

// Копирует строку, на которую указывает src, в dest.
char *s21_strcpy(char *dest, const char *src) {
  char *res = dest;
  while ((*dest++ = *src++)) {
  }
  return res;
}

// Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *res = dest;
  while (n && (*dest = *src)) {
    dest++;
    src++;
    n--;
  }
  return res;
}

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке. Нужно объявить макросы,
// содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке.
// Проверка текущей ОС осуществляется с помощью директив.
char *s21_strerror(int errnum) {
  static char res[MAX_ERROR_LEN];
  if (errnum < 0 || errnum >= MAX_ERROR || ERRLIST[errnum] == NULL) {
    s21_sprintf(res, "Unknown error %d", errnum);
  } else {
    s21_strncpy(res, ERRLIST[errnum], MAX_ERROR_LEN - 1);
  }
  return res;
}
// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;
  while (*str1) {
    const char *ptr = str2;
    while (*ptr) {
      if (*str1 == *ptr++) {
        res = (char *)str1;
        break;
      }
    }
    if (res != S21_NULL) {
      break;
    }
    str1++;
  }
  return res;
}

// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strrchr(const char *str, int c) {
  char *res = S21_NULL;
  if (str != S21_NULL) {
    if (c == '\0') {
      res = s21_strchr(str, '\0');
    } else {
      char *temp = (char *)str;
      s21_size_t size = s21_strlen(str);
      while (size != 0) {
        size--;
        if (temp[size] == c) {
          res = &temp[size];
          break;
        }
      }
    }
  }
  return res;
}

// Находит первое вхождение всей строки needle
// (не включая завершающий нулевой символ), которая появляется в строке
// haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;
  int len1 = s21_strlen(haystack);
  int len2 = s21_strlen(needle);
  if (len1 >= len2) {
    for (s21_size_t i = 0; i < s21_strlen(haystack); i++) {
      s21_size_t count = 0;
      for (s21_size_t j = 0; j < s21_strlen(needle); j++) {
        if (haystack[i] == needle[0] && haystack[i + j] == needle[j]) {
          count += 1;
        }
      }
      if (count == s21_strlen(needle)) {
        res = (char *)haystack + i;
        break;
      }
    }
  }
  return res;
}

// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char *static_str = S21_NULL;
  if (str == S21_NULL) str = static_str;
  for (; str && *str && s21_strchr(delim, *str); str++) {
  }
  if (str && *str == '\0') {
    str = S21_NULL;
    static_str = S21_NULL;
  }
  if (str && *str == '\0') {
    str = S21_NULL;
    static_str = S21_NULL;
  }
  if (str && *str != '\0') {
    static_str = str;
    for (; *static_str && !(s21_strchr(delim, *static_str)); static_str++) {
    }
  }
  if (static_str && *static_str) {
    *static_str = '\0';
    static_str++;
  }
  if (static_str && *static_str == '\0') {
    static_str = S21_NULL;
  }
  return str;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  while (*str1 && !s21_strchr(str2, *str1++)) {
    res++;
  }
  return res;
}

// Вычисляет длину строки str, не включая завершающий нулевой символ.
s21_size_t s21_strlen(const char *str) {
  s21_size_t res = 0;
  while (str[res] != '\0') {
    res++;
  }
  return res;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов str2.
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  while (*str1 && s21_strchr(str2, *str1++)) {
    res++;
  }
  return res;
}

// Возвращает копию строки (str), преобразованной в верхний регистр.
// В случае какой-либо ошибки следует вернуть значение NULL

void *s21_to_upper(const char *str) {
  char *res = S21_NULL;
  s21_size_t size = s21_strlen(str);
  res = (char *)calloc(size + 1, 1);
  if (res != S21_NULL) {
    s21_strcpy(res, str);
    for (s21_size_t iterator = 0; iterator < size + 1; iterator++) {
      if (res[iterator] >= 97 && res[iterator] <= 122) {
        res[iterator] -= 32;
      }
    }
  }
  return (void *)res;
}

// Возвращает копию строки (str), преобразованной в нижний регистр.
// В случае какой-либо ошибки следует вернуть значение NULL

void *s21_to_lower(const char *str) {
  char *res = S21_NULL;
  s21_size_t size = s21_strlen(str);
  res = (char *)calloc(size + 1, 1);
  if (res != S21_NULL) {
    s21_strcpy(res, str);
    for (s21_size_t iterator = 0; iterator < size + 1; iterator++) {
      if (res[iterator] >= 65 && res[iterator] <= 90) {
        res[iterator] += 32;
      }
    }
  }
  return (void *)res;
}

// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL

// more checks!
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;
  if (src && str && start_index <= (s21_strlen(src))) {
    s21_size_t size1 = s21_strlen(src), size2 = s21_strlen(str);
    res = (char *)calloc(size1 + size2 + 1, 1);
    if (res != S21_NULL) {
      for (s21_size_t i = 0; i < start_index; i++) {
        res[i] = src[i];
      }
      for (s21_size_t i = start_index; i < size2 + start_index; i++) {
        res[i] = str[i - start_index];
      }
      for (s21_size_t i = size2 + start_index; i < size2 + size1; i++) {
        res[i] = src[i - size2];
      }
    }
  }
  return (void *)res;
}

// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src).
// В случае какой-либо ошибки следует вернуть значение NULL

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;
  if (src) {
    char *reversed_src = trim_reverse(src);
    s21_size_t face = s21_strspn(src, trim_chars);
    s21_size_t tail = s21_strspn(reversed_src, trim_chars);
    s21_size_t size = s21_strlen(src);
    res = (char *)calloc(size - face - tail + 1, 1);
    if (res != S21_NULL) {
      char *ptr1 = (char *)src + face, *ptr2 = (char *)(src + size - tail);
      char *temp = res;
      while (ptr1 != ptr2) {
        *temp++ = *ptr1++;
      }
    }
    free(reversed_src);
  }
  return (void *)res;
}

// доп функция для реверса(далее - подсчет кол-ва символов с конца строки)
char *trim_reverse(const char *src) {
  char *res = S21_NULL;
  s21_size_t size = s21_strlen(src);
  res = (char *)calloc(size + 1, 1);
  if (res != S21_NULL) {
    for (int i = size - 1; i >= 0; i--) {
      res[size - i - 1] = src[i];
    }
  }
  return res;
}