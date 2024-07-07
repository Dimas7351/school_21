#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *strPtr = str;
  va_list args;
  va_start(args, format);
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      Token token = parseTokenSP(&format, &args);
      handleTokenSP(token, &str, args, strPtr);
    }
  }
  *str = '\0';
  va_end(args);
  return str - strPtr;
}

Token parseTokenSP(const char **format, va_list *args) {
  Token newToken = {0};
  parseFlags(&newToken, format);
  parseWidth(&newToken, format, args);
  parseAccurasy(&newToken, format, args);
  parseLenght(&newToken, format);
  parseSpec(&newToken, format);
  return newToken;
};

void parseFlags(Token *token, const char **format) {
  while (**format == '0' || **format == '-' || **format == '+' ||
         **format == '#' || **format == ' ') {
    switch (**format) {
      case '0':
        token->Flags.NULL_F = true;
        break;
      case '+':
        token->Flags.PLUS_F = true;
        break;
      case '-':
        token->Flags.MINUS_F = true;
        break;
      case '#':
        token->Flags.SHARP_F = true;
        break;
      case ' ':
        token->Flags.SPACE_F = true;
        break;
    }
    (*format)++;
  }
}

void parseWidth(Token *token, const char **format, va_list *args) {
  if (**format == '*') {
    (*format)++;
    token->Width = va_arg(*args, int);
  } else if (isBasedDigit(**format, 10)) {
    s21_size_t width = 0;
    while (isBasedDigit(**format, 10)) {
      width = width * 10 + (**format - '0');
      (*format)++;
    }
    token->Width = width;
  }
  if (**format == '.') {
    (*format)++;
    token->Flags.ACCURACY = true;
  }
}

void parseAccurasy(Token *token, const char **format, va_list *args) {
  if (**format == '*') {
    (*format)++;
    token->Accuracy = va_arg(*args, int);
  } else if (isBasedDigit(**format, 10)) {
    s21_size_t accuracy = 0;
    while (isBasedDigit(**format, 10)) {
      accuracy = accuracy * 10 + (**format - '0');
      (*format)++;
    }
    token->Accuracy = accuracy;
  }
}

void parseLenght(Token *token, const char **format) {
  if (**format == 'l') {
    token->LType = LONG_L;
    (*format)++;
  } else if (**format == 'L') {
    token->LType = LONG_DOUBLE_L;
    (*format)++;
  } else if (**format == 'h') {
    token->LType = SHORT_L;
    (*format)++;
  }
}

void parseSpec(Token *token, const char **format) {
  token->Spec = **format;
  (*format)++;
}

void handleTokenSP(Token token, char **str, va_list args, char *strPtr) {
  char *buffer = calloc(BUFF_SIZE, 1);
  bool isCharNull = false;
  if (token.Spec == 'd' || token.Spec == 'i') {
    parseIntSP(&token, &buffer, args);
  } else if (token.Spec == 'u') {
    parseUnsignedSP(&token, &buffer, args);
  } else if (token.Spec == 'x' || token.Spec == 'X') {
    parseHexSP(&token, &buffer, args);
  } else if (token.Spec == 'f') {
    parseFloatSP(&token, &buffer, args);
  } else if (token.Spec == 'e' || token.Spec == 'E') {
    parseExpSP(&token, &buffer, args);
  } else if (token.Spec == 'g' || token.Spec == 'G') {
    parseSciSP(&token, &buffer, args);
  } else if (token.Spec == 's') {
    parseStrSP(&token, &buffer, args);
  } else if (token.Spec == 'c') {
    isCharNull = parseCharSP(&token, &buffer, args);
  } else if (token.Spec == 'p') {
    parsePointerSP(&token, &buffer, args);
  } else if (token.Spec == 'o') {
    parseOctalSP(&token, &buffer, args);
  } else if (token.Spec == 'n') {
    *(va_arg(args, int *)) = *str - strPtr;
  } else if (token.Spec == '%') {
    buffer[0] = '%';
  }
  for (int i = 0; buffer[i]; i++, (*str)++) {
    **str = buffer[i];
  }
  if (isCharNull) {
    **str = '\0';
    (*str)++;
  }
  free(buffer);
}

void handleFlags(Token *token, char **buffer) {
  char temp[BUFF_SIZE] = {0};
  bool sign = ((*buffer)[0] == '-') ? true : false;
  if ((token->Flags.PLUS_F && token->Spec != 'u')) {
    temp[0] = sign ? '-' : '+';
    s21_strcpy(temp + 1, sign ? (*buffer) + 1 : *buffer);
    s21_strcpy(*buffer, temp);
    sign = true;
  } else if ((token->Flags.SPACE_F && (*buffer)[0] != '-' &&
              token->Spec != 'u')) {
    temp[0] = ' ';
    s21_strcpy(temp + 1, *buffer);
    s21_strcpy(*buffer, temp);
    sign = true;
  } else {
    s21_strcpy(temp, *buffer);
  }
  s21_size_t size = s21_strlen(*buffer);
  if (token->Width > (int)size) {
    int diff = token->Width - size;
    if (token->Flags.MINUS_F) {
      s21_strcpy(temp, *buffer);
      s21_memset(temp + s21_strlen(temp), ' ', diff);
    } else {
      bool nulls = token->Flags.NULL_F;
      // если нули и сигна = поставить в 0 сигну и закрыть нулями
      // если нули = закрыть нулями, если сигна онли = закрыть пробелами,
      // сигну после пробелов
      if (sign && temp[0] != '+' && temp[0] != ' ') {
        temp[0] = '-';
      };
      s21_memset(nulls ? sign ? temp + 1 : temp : temp, nulls ? '0' : ' ',
                 diff);
      s21_strcpy(nulls ? sign ? temp + diff + 1 : temp + diff : temp + diff,
                 nulls ? sign ? (*buffer) + 1 : *buffer : *buffer);
    }
  }
  if (s21_strlen(temp) != 0) {
    s21_strcpy((*buffer), temp);
  }
}

void handleAccuracy(Token *token, char **buffer) {
  char *temp = calloc(BUFF_SIZE, 1);
  bool neg = false;
  s21_size_t size = s21_strlen(*buffer);
  if ((*buffer)[0] == '-') {
    temp[0] = '-';
    neg = true;
    size--;
  }
  if (token->Accuracy > (int)size) {
    int ptr = neg;
    while (ptr < (int)(token->Accuracy - size + neg)) {
      temp[ptr] = '0';
      ptr++;
    }
    for (int i = neg; (*buffer)[i]; i++, ptr++) {
      temp[ptr] = (*buffer)[i];
    }
    s21_strcpy(*buffer, temp);
  }
  free(temp);
}

void handleSciAccurracy(char **buffer, int accuracy) {
  int digits = 0;
  s21_size_t len = s21_strlen(*buffer);
  int nullNotFound = 0;
  for (s21_size_t i = 0; i < s21_strlen(*buffer); i++) {
    if (((*buffer)[i] == '0' && !nullNotFound) || (*buffer)[i] == '.')
      continue;
    else
      nullNotFound = 1;
    if (isBasedDigit((*buffer)[i], 10) && nullNotFound) {
      digits++;
    }
    if (digits == accuracy && i + 1 < len) {
      int next = (*buffer)[i + 1] == '.' ? 2 : 1;
      if ((*buffer)[i + next] - '0' >= 5) {
        (*buffer)[i] = (char)(*buffer)[i] + 1;
        if ((*buffer)[i] == ':') {
          (*buffer)[i - 1] = (char)(*buffer)[i - 1] + 1;
          (*buffer)[i] = '0';
        }
      }
      (*buffer)[i + 1] = '\0';
      break;
    }
  }
}

void parseIntSP(Token *token, char **buffer, va_list args) {
  int64_t value = va_arg(args, int64_t);
  if (token->LType == SHORT_L) {
    value = (int16_t)value;
  } else if (token->LType == NONE_L) {
    value = (int32_t)value;
  }
  if (value == 0 && token->Flags.ACCURACY && token->Accuracy == 0) {
    **buffer = '\0';
  } else {
    numToBuffer(value, 10, buffer);
    reverse(buffer);
    handleAccuracy(token, buffer);
    handleFlags(token, buffer);
  }
}

void parseUnsignedSP(Token *token, char **buffer, va_list args) {
  uint64_t value = va_arg(args, uint64_t);
  if (token->LType == SHORT_L) {
    value = (uint16_t)value;
  } else if (token->LType == NONE_L) {
    value = (uint32_t)value;
  }
  unsignedToBuffer(value, 10, buffer);
  reverse(buffer);
  handleAccuracy(token, buffer);
  handleFlags(token, buffer);
}

void parseStrSP(Token *token, char **buffer, va_list args) {
  char temp[BUFF_SIZE] = {0};
  char *str = va_arg(args, char *);
  if (str == S21_NULL) {
    s21_strcpy(*buffer, "(null)");
  } else {
    s21_strcpy(temp, str);
    if (token->Accuracy) {
      temp[token->Accuracy] = 0;
    }
    s21_strcpy(*buffer, temp);
    token->Flags.NULL_F = token->Flags.PLUS_F = 0;
    token->Flags.SHARP_F = token->Flags.SPACE_F = 0;
    handleFlags(token, buffer);
  }
}

bool parseCharSP(Token *token, char **buffer, va_list args) {
  bool isCharNull = false;
  char c;
  c = va_arg(args, int);
  if (c == 0) {
    isCharNull = true;
  }
  (*buffer)[0] = c;
  token->Flags.NULL_F = token->Flags.PLUS_F = 0;
  token->Flags.SHARP_F = token->Flags.SPACE_F = 0;
  handleFlags(token, buffer);
  return isCharNull;
}

void parsePointerSP(Token *token, char **buffer, va_list args) {
  uint64_t val = va_arg(args, uint64_t);
  if (val == 0) {
    s21_strcpy(*buffer, "(nil)");
  } else {
    unsignedToBuffer(val, 16, buffer);
    reverse(buffer);
    handleAccuracy(token, buffer);
    reverse(buffer);
    s21_size_t len = s21_strlen(*buffer);
    (*buffer)[len + 1] = '0';
    (*buffer)[len] = 'x';
    reverse(buffer);
    token->Flags.NULL_F = token->Flags.SHARP_F = 0;
    handleFlags(token, buffer);
  }
}

void parseHexSP(Token *token, char **buffer, va_list args) {
  uint64_t val = va_arg(args, uint64_t);
  if (token->LType == NONE_L) {
    val = (uint32_t)val;
  } else if (token->LType == SHORT_L) {
    val = (uint16_t)val;
  }
  unsignedToBuffer(val, 16, buffer);
  reverse(buffer);
  handleAccuracy(token, buffer);
  bool isNotNullsOnly = false;
  for (int i = s21_strlen(*buffer) - 1; i >= 0; i--) {
    if ((*buffer)[i] != '0') {
      isNotNullsOnly = true;
    }
  }
  if (isNotNullsOnly && token->Flags.SHARP_F) {
    reverse(buffer);
    s21_size_t len = s21_strlen(*buffer);
    (*buffer)[len + 1] = '0';
    (*buffer)[len] = 'x';
    reverse(buffer);
  }
  token->Flags.PLUS_F = token->Flags.SPACE_F = 0;
  handleFlags(token, buffer);
  if (token->Spec == 'X') {
    toUpperSP(buffer);
  } else if (token->Spec == 'x') {
    toLowerSP(buffer);
  }
}

void parseOctalSP(Token *token, char **buffer, va_list args) {
  uint64_t val = va_arg(args, uint64_t);
  numToBuffer(val, 8, buffer);
  s21_size_t size = s21_strlen(*buffer);
  if (token->Flags.SHARP_F) {
    (*buffer)[size] = '0';
  }
  reverse(buffer);
  handleAccuracy(token, buffer);
  token->Flags.PLUS_F = 0;
  token->Flags.SPACE_F = 0;
  handleFlags(token, buffer);
}

void parseFloatSP(Token *token, char **buffer, va_list args) {
  long double val = 0;
  if (token->LType == LONG_DOUBLE_L) {
    val = va_arg(args, long double);
  } else {
    val = va_arg(args, double);
  }
  if (!token->Flags.ACCURACY) {
    token->Accuracy = 6;
  }
  floatToBuffer(token, val, buffer);
  handleFlags(token, buffer);
}

void parseExpSP(Token *token, char **buffer, va_list args) {
  long double val = 0;
  if (token->LType == LONG_DOUBLE_L) {
    val = va_arg(args, long double);
  } else {
    val = va_arg(args, double);
  }
  int e = 0, sign = (int)val == 0 ? '-' : '+';
  double floatPart = (int)val - val;
  if (floatPart) {
    while ((long long int)val == 0) {
      e++;
      val *= 10;
    }
  } else {
    sign = '+';
  }
  while ((long long int)val / 10 != 0) {
    e++;
    val /= 10;
  }
  if (!token->Flags.ACCURACY) {
    token->Accuracy = 6;
  }
  floatToBuffer(token, val, buffer);
  expToBuffer(buffer, sign, e);
  if (token->Spec == 'E') {
    toUpperSP(buffer);
  }
  handleFlags(token, buffer);
}

void parseSciSP(Token *token, char **buffer, va_list args) {
  long double val = 0;
  if (token->LType == LONG_DOUBLE_L) {
    val = va_arg(args, long double);
  } else {
    val = va_arg(args, double);
  }
  int posE = 0, negE = 0;
  if (!token->Flags.ACCURACY) {
    token->Accuracy = 6;
  }
  if (!token->Accuracy) {
    token->Accuracy = 1;
  }
  long double intPart = val;
  for (; (int)intPart / 10; intPart /= 10, posE++) {
  };
  long double floatPart = val;
  if (!posE) {
    if ((int)val - val) {
      for (; !((int)floatPart); negE++, floatPart *= 10) {
      }
    }
    floatPart = roundl(floatPart * 10e+10) / 10e10;
  }
  if (posE >= token->Accuracy) {
    floatToBuffer(token, intPart, buffer);
  } else if (negE > 4) {
    floatToBuffer(token, floatPart, buffer);
  } else if (token->Flags.ACCURACY && negE > token->Accuracy) {
    token->Accuracy = negE;
    floatToBuffer(token, val, buffer);
  } else {
    floatToBuffer(token, val, buffer);
  }
  handleSciAccurracy(buffer, token->Accuracy);
  if (!token->Flags.SHARP_F) removeNulls(token, buffer);
  if (posE >= token->Accuracy) {
    expToBuffer(buffer, '+', posE);
  } else if (negE > 4) {
    expToBuffer(buffer, '-', negE);
  }
  if (token->Spec == 'G') {
    toUpperSP(buffer);
  }
  handleFlags(token, buffer);
}

void floatToBuffer(Token *token, long double num, char **buffer) {
  char *bufferInt = calloc(BUFF_SIZE, 1);
  char *bufferFloat = calloc(BUFF_SIZE, 1);
  bool neg = num < -1e-15 ? true : false;
  num = neg ? -num : num;
  long double intPart = 0, floatPart = modfl(num, &intPart);
  floatPart = token->Accuracy ? floatPart : 0;
  intPart = token->Accuracy ? intPart : roundl(num);
  int i = 0;
  for (int j = 0; j < token->Accuracy; j++) {
    floatPart *= 10;
  }
  long long right = roundl(floatPart);
  if ((token->Flags.ACCURACY && token->Accuracy != 0) ||
      (!token->Flags.ACCURACY && num == 0) || (long long int)floatPart ||
      token->Accuracy || token->Flags.SHARP_F) {
    bufferInt[i] = '.', i++;
  }
  if (intPart) {
    for (; (long long int)intPart != 0; i++, intPart /= 10) {
      bufferInt[i] = "0123456789"[(long long int)intPart % 10];
    }
  } else {
    bufferInt[i] = '0', i += 1;
  }
  if (neg) {
    bufferInt[i] = '-';
  };
  reverse(&bufferInt);
  for (int j = 0; j < token->Accuracy || right; j++, right /= 10) {
    bufferFloat[j] = "0123456789"[(long long int)(right % 10 + 0.001)];
  }
  reverse(&bufferFloat);
  bufferInt = s21_strcat(bufferInt, bufferFloat);
  s21_strcpy(*buffer, bufferInt);
  free(bufferInt);
  free(bufferFloat);
}

void numToBuffer(int64_t num, int base, char **buffer) {
  char *temp = *buffer;
  bool negative = false;
  if (num < 0) {
    negative = true;
    num *= -1;
  }
  if (num == 0) {
    *temp = '0';
    temp++;
  }
  while (num != 0) {
    *temp = "0123456789abcdef"[num % base];
    num /= base;
    temp++;
  }
  if (negative) {
    *temp = '-';
  };
}

void expToBuffer(char **buffer, int sign, int e) {
  s21_size_t size = s21_strlen(*buffer);
  (*buffer)[size] = 'e';
  (*buffer)[size + 1] = sign;
  (*buffer)[size + 2] = ("0123456789"[(e / 10) % 10]);
  (*buffer)[size + 3] = ("0123456789"[e % 10]);
}

void removeNulls(Token *token, char **buffer) {
  int len = s21_strlen(*buffer);
  char *dot = S21_NULL;
  dot = s21_strchr(*buffer, '.');
  if (dot) {
    for (int i = len - 1; *(*buffer + i) != '.'; i--) {
      if ((*buffer)[i] == '0') {
        (*buffer)[i] = '\0';
      } else {
        break;
      }
    }
    if (!token->Flags.SHARP_F && *(dot + 1) == '\0') *dot = '\0';
  }
}

void unsignedToBuffer(uint64_t num, int base, char **buffer) {
  char *temp = *buffer;
  if (num == 0) {
    *temp = '0';
    temp++;
  }
  while (num != 0) {
    *temp = "0123456789abcdef"[num % base];
    num /= base;
    temp++;
  }
}

void reverse(char **str) {
  char temp[BUFF_SIZE] = {0};
  int size = (int)s21_strlen(*str);
  for (int i = size - 1; i >= 0; i--) {
    temp[size - i - 1] = (*str)[i];
  }
  for (int i = 0; i < size; i++) {
    (*str)[i] = temp[i];
  }
}

void toUpperSP(char **str) {
  s21_size_t size = s21_strlen(*str);
  for (s21_size_t i = 0; i < size; i++) {
    if ((*str)[i] >= 'a' && (*str)[i] <= 'z') {
      (*str)[i] -= 32;
    }
  }
}

void toLowerSP(char **str) {
  s21_size_t size = s21_strlen(*str);
  for (s21_size_t i = 0; i < size; i++) {
    if ((*str)[i] >= 'A' && (*str)[i] <= 'Z') {
      (*str)[i] += 32;
    }
  }
}