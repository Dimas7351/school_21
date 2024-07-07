#include "s21_sscanf.h"

static bool noRead = false;

// Возвращает либо int засканенных аргументов, либо eof в случае говна
int s21_sscanf(const char *str, const char *format, ...) {
  int res = 0, res_eof = isEOF(str) || isEOF(format);
  if (!res_eof) {
    va_list args;
    va_start(args, format);
    char *sptr = (char *)str;
    char *fptr = (char *)format;
    s21_size_t start = s21_strlen(str);
    // пришел токен - обработали - двигаемся дальше
    while (*sptr && *fptr && res != -1) {
      Token token = parseToken(&fptr, &sptr);
      if (!handleToken(token, &sptr, args, &res, start)) break;
    }
    va_end(args);
  }
  return (res_eof) ? -res_eof : res;
}

// парс токенов и последующее форматирование
Token parseToken(char **fptr, char **sptr) {
  Token newToken = {0};
  if (isSpace(**fptr)) {
    newToken.spec = ' ';
    while (**fptr && isSpace(**fptr)) {
      (*fptr)++;
    }
  }
  if (**fptr == '%' && newToken.spec == 0) {
    (*fptr)++;
    parseW(&newToken, fptr);
    parseL(&newToken, fptr);
    newToken.spec = (**fptr);
    (*fptr)++;
  } else if (newToken.spec == 0 && **sptr == **fptr) {
    for (; **sptr && **fptr && **fptr != '%' && **sptr == **fptr;
         (*fptr)++, (*sptr)++) {
    }
    if (**fptr == '%') {
      (*fptr)++;
      parseW(&newToken, fptr);
      parseL(&newToken, fptr);
      newToken.spec = (**fptr);
      (*fptr)++;
    }
  }
  return newToken;
}

// парс ширины + учесть дискрипшны (num, asterisk)
void parseW(Token *token, char **fptr) {
  // конвертировать буффер цифр в в число;
  if (**fptr == '*') {
    token->widthType = ASTERIKS_W;
    (*fptr)++;
  } else if (isBasedDigit(**fptr, 10)) {
    char fullNum[1024] = {'\0'};
    s21_size_t iterator = 0;
    while (**fptr && isBasedDigit(**fptr, 10)) {
      fullNum[iterator] = **fptr;
      iterator++;
      (*fptr)++;
    }
    token->width = s21_atoi(fullNum);
    token->widthType = token->width == 0 ? NONE_W : NUMBER_W;
  }
}

// парс длины, учесть дискрипшны(l, L, h)
void parseL(Token *token, char **fptr) {
  if (**fptr == 'l') {
    token->lenght = LONG_L;
    (*fptr)++;
    if (**fptr == 'l') {
      token->lenght = LONG_LONG_L;
      (*fptr)++;
    }
  } else if (**fptr == 'L') {
    token->lenght = LONG_DOUBLE_L;
    (*fptr)++;
  } else if (**fptr == 'h') {
    token->lenght = SHORT_L;
    (*fptr)++;
  }
}

bool handleToken(Token token, char **sptr, va_list args, int *res,
                 s21_size_t start) {
  bool ok = true;
  // handle all funcs
  if (token.spec == ' ') {
    handleSpaceSpec(sptr);
  } else if (token.spec == 's' || token.spec == 'c') {
    *res += handleCSSpec(token, args, sptr);
  } else if (token.spec == 'd') {
    *res += handleIntSpec(token, args, sptr);
  } else if (token.spec == 'i') {
    *res += handleISpec(token, args, sptr);
  } else if (token.spec == 'e' || token.spec == 'E' || token.spec == 'g' ||
             token.spec == 'G' || token.spec == 'f') {
    *res += handleEefGgSpec(token, args, sptr);
  } else if (token.spec == 'o') {
    *res += handleOSpec(token, args, sptr);
  } else if (token.spec == 'u') {
    *res += handleUInt(token, args, sptr, 10, false);
  } else if (token.spec == 'x' || token.spec == 'X') {
    *res += handleXxSpec(token, args, sptr);
  } else if (token.spec == 'p') {
    *res += handlePSpec(token, args, sptr);
  } else if (token.spec == 'n') {
    *res += handleCount(args, sptr, start);
  } else if (token.spec == '%') {
    handlePercentSpec(sptr);
  } else {
    ok = false;
  }
  return ok;
}

void handleSpaceSpec(char **sptr) {
  while (**sptr && isSpace(**sptr)) {
    (*sptr)++;
  }
}

void handlePercentSpec(char **sptr) {
  while (**sptr && **sptr != '%') {
    (*sptr)++;
  }
  if (**sptr == '%') {
    (*sptr)++;
  }
}

int handlePSpec(Token token, va_list args, char **sptr) {
  token.lenght = LONG_L;
  bool found = parseHex(token, args, sptr);
  return found;
}

int handleCSSpec(Token token, va_list args, char **sptr) {
  bool found = parseStr(token, sptr, args);
  return found;
}

int handleEefGgSpec(Token token, va_list args, char **sptr) {
  long double res = 0;
  bool found = parseFloat(token, sptr, &res);
  if (found) {
    if (token.widthType == ASTERIKS_W) {
      found = false;
    } else if (token.lenght == LONG_DOUBLE_L) {
      *(va_arg(args, long double *)) = res;
    } else if (token.lenght == LONG_L) {
      *(va_arg(args, double *)) = (double)res;
    } else {
      *(va_arg(args, float *)) = (float)res;
    }
  }
  return found;
}

int handleISpec(Token token, va_list args, char **sptr) {
  skipSpaces(sptr);
  bool found = false;
  if (**sptr == '0' && (*(*sptr + 1) == 'x' || *(*sptr + 1) == 'X')) {
    found = handleXxSpec(token, args, sptr);
  } else if (**sptr == '0') {
    found = handleOSpec(token, args, sptr);
  } else {
    found = handleIntSpec(token, args, sptr);
  }
  return found;
}

int handleOSpec(Token token, va_list args, char **sptr) {
  return parseOctal(token, args, sptr);
}

int handleXxSpec(Token token, va_list args, char **sptr) {
  return parseHex(token, args, sptr);
}

int handleIntSpec(Token token, va_list args, char **sptr) {
  long long res = 0;
  bool found = parseInt(token, sptr, &res);
  if (found) {
    if (token.widthType == ASTERIKS_W) {
      found = false;
    } else if (token.lenght == NONE_L) {
      *(va_arg(args, int *)) = (int)res;
    } else if (token.lenght == SHORT_L) {
      *(va_arg(args, short *)) = (short)res;
    } else if (token.lenght == LONG_L) {
      *(va_arg(args, long *)) = (long)res;
    } else if (token.lenght == LONG_LONG_L) {
      *(va_arg(args, long long *)) = (long long)res;
    }
  }
  return found;
}

int handleUInt(Token token, va_list args, char **sptr, int base, bool n) {
  unsigned long long res = 0;
  bool found = 0;
  if ((token.spec == 'x' || token.spec == 'X') && (**sptr == ' ' || !**sptr)) {
    found = true;
  } else {
    found = parseUint(token, sptr, &res, base, n) || n;
  }
  if (found || (token.spec == 'o' && (**sptr == 'x' || **sptr == 'X'))) {
    if (token.widthType == ASTERIKS_W) {
      found = false;
    } else if (token.lenght == NONE_L) {
      *(va_arg(args, unsigned int *)) = (unsigned int)res;
    } else if (token.lenght == SHORT_L) {
      *(va_arg(args, unsigned short *)) = (unsigned short)res;
    } else if (token.lenght == LONG_L) {
      *(va_arg(args, unsigned long *)) = (unsigned long)res;
    } else if (token.lenght == LONG_LONG_L) {
      *(va_arg(args, unsigned long long *)) = (unsigned long long)res;
    }
  }
  return found;
}

int parseStr(Token token, char **sptr, va_list args) {
  bool found = false;
  char *dest = S21_NULL;
  s21_size_t width = 0;
  if (token.spec == 's') {
    while (**sptr && isSpace(**sptr)) {
      (*sptr)++;
    }
  }
  s21_size_t non_empty = s21_strcspn(*sptr, " \t");
  if ((token.width == 0 && token.spec == 'c') ||
      (token.spec == 'c' && token.widthType == ASTERIKS_W)) {
    width = 1;
  } else if ((token.width == 0 && token.spec == 's') ||
             (int)non_empty < token.width || token.widthType == ASTERIKS_W) {
    width = non_empty;
  } else {
    width = token.width;
  }
  if (token.widthType != ASTERIKS_W) {
    dest = va_arg(args, char *);
    s21_strncpy(dest, *sptr, width);
    if (token.spec == 's') {
      dest[width] = '\0';
    }
    found = true;
  }
  *sptr += width;
  return found;
}

int parseInt(Token token, char **sptr, long long *dest) {
  skipSpaces(sptr);
  bool negative = false, isWGreater = false;
  s21_size_t strLen = s21_strlen(*sptr);
  if (token.width > (int)strLen && token.widthType == NUMBER_W) {
    isWGreater = true;
  }
  long long int res = 0;
  if (token.widthType == NONE_W || token.widthType == ASTERIKS_W) {
    token.width = MAX_INT;
  }
  isNegative(&negative, &token.width, sptr);
  bool overflow = false, found = false;
  if (!noRead && isBasedDigit(**sptr, 10) && token.width != 0) {
    found = true;
  } else if (isBasedDigit(**sptr, 10) && token.width == 0) {
    noRead = true;
    (*sptr)--;
  }
  if (found == true) {
    while (isBasedDigit(**sptr, 10) && token.width--) {
      if (res > (MAX_LLONG - (**sptr - '0') / 10)) {
        found = false;
        overflow = true;
        res = MAX_LLONG;
        if (negative == true) {
          res = -res - 1;
        }
        break;
      }
      res = res * 10 + (**sptr - '0');
      (*sptr)++;
    }
  }
  if (negative && found) res = -res;
  if (found || overflow) *dest = res;
  if (isWGreater) *sptr += token.width;
  return found || overflow;
}

int parseUint(Token token, char **sptr, unsigned long long *dest, int base,
              bool negative) {
  skipSpaces(sptr);
  bool overflow = false, found = false;
  if (token.widthType == NONE_W || token.widthType == ASTERIKS_W) {
    token.width = MAX_INT;
  }
  unsigned long long res = 0;
  if (**sptr && !negative) isNegative(&negative, &token.width, sptr);
  if (**sptr && !noRead && isBasedDigit(**sptr, base) && token.width != 0) {
    found = true;
  } else if (isBasedDigit(**sptr, 10) && token.width == 0) {
    noRead = true;
    (*sptr)--;
  }

  if (found) {
    while (isBasedDigit(**sptr, base) && token.width--) {
      if (res > (MAX_ULONG - fromBasedDigit(**sptr, base)) / base) {
        found = false;
        overflow = true;
        res = MAX_ULONG;
        if (negative == true) {
          res = -res - 1;
        }
        while (**sptr && token.width--) {
          (*sptr)++;
        }
      } else {
        res = res * base + fromBasedDigit(**sptr, base);
        (*sptr)++;
      }
    }
    if (negative && found) {
      res = -res;
    }
    *dest = res;
  }
  return found || overflow;
}

int parseFloat(Token token, char **sptr, long double *dest) {
  skipSpaces(sptr);
  bool found = false, negative = false;
  if (token.widthType == NONE_W || token.widthType == ASTERIKS_W) {
    token.width = MAX_INT;
  }
  isNegative(&negative, &token.width, sptr);
  if (isNANINF(sptr, negative, dest)) {
    found = true;
  } else if (isBasedDigit(**sptr, 10) || **sptr == '.') {
    s21_size_t numsCount = 0;
    *dest = s21_atof(sptr, negative, &token.width, &numsCount);
    if (numsCount == 0) {
      found = false;
    } else {
      found = true;
    }
  }
  return found;
}

int parseOctal(Token token, va_list args, char **sptr) {
  skipSpaces(sptr);
  bool found = false, negative = false;
  isNegative(&negative, &token.width, sptr);
  if (**sptr == '0') {
    (*sptr)++;
    token.width--;
    found = true;
  }
  found |= handleUInt(token, args, sptr, 8, negative);
  return found;
}

int parseHex(Token token, va_list args, char **sptr) {
  skipSpaces(sptr);
  bool found = false, negative = false;
  isNegative(&negative, &token.width, sptr);
  if (**sptr == '0' && (*(*sptr + 1) == 'x' || *(*sptr + 1) == 'X')) {
    *sptr = *sptr + 2;
    found = true;
  }
  found = handleUInt(token, args, sptr, 16, negative);
  return found;
}

int handleCount(va_list args, char **sptr, s21_size_t start) {
  int current = s21_strlen(*sptr);
  int len = (start - current);
  if (len > 0) {
    *(va_arg(args, int *)) = (start - current);
  } else {
    *(va_arg(args, int *)) = 0;
  }
  return 0;
}

int isEOF(const char *ptr) {
  int res = true;
  if (ptr != S21_NULL) {
    while (*ptr) {
      if (!isSpace(*ptr) && *ptr != '\0') {
        res = false;
        break;
      }
      ptr++;
    }
  }
  return res;
}

bool isSpace(char c) { return (c == '\t' || c == '\n' || c == ' '); }

bool isNANINF(char **sptr, bool negative, long double *dest) {
  bool found = false;
  char *lowerPtr = s21_to_lower(*sptr);
  if (!s21_strncmp(lowerPtr, "nan", 3)) {
    *dest = NAN;
    found = true;
  } else if (!s21_strncmp(lowerPtr, "inf", 3)) {
    *dest = INFINITY;
    found = true;
  }
  if (found && negative) {
    *dest *= -1;
  }
  if (found) {
    *sptr += 3;
  }
  free(lowerPtr);
  return found;
}

bool isExp(char **sptr, int *e, int *width) {
  bool res = false;
  if (**sptr == 'e' || **sptr == 'E') {
    bool isNegative = 0;
    (*sptr)++;
    if (**sptr && **sptr == '+') {
      (*sptr)++;
    } else if (**sptr && **sptr == '-') {
      isNegative = true;
      (*sptr)++;
    }
    while (**sptr && *width-- && isBasedDigit(**sptr, 10)) {
      *e = *e * 10 + (**sptr - '0');
      (*sptr)++;
    }
    if (isNegative) {
      *e *= -1;
    }
    res = true;
  }
  return res;
}

bool isBasedDigit(char c, int b) {
  bool res;
  if (b > 10) {
    res = (c >= '0' && c <= '9') || (c >= 'a' && c < 'a' + b - 10) ||
          (c >= 'A' && c < 'A' + b - 10);
  } else {
    res = c >= '0' && c < '0' + b;
  }
  return res;
}

void isNegative(bool *neg, int *width, char **sptr) {
  if (**sptr == '-') {
    (*sptr)++;
    *width = *width - 1;
    *neg = true;
  } else if (**sptr == '+') {
    (*sptr)++;
    *width = *width - 1;
  }
  if (**sptr == '-' || **sptr == '+') {
    (*sptr)--;
  }
}

unsigned long fromBasedDigit(char c, int base) {
  unsigned long res = 0;
  if (base <= 10) {
    res = c - '0';
  } else {
    if (c <= '9') {
      res = c - '0';
    } else if (c < 'A' - 10 + base) {
      res = c - 'A' + 10;
    } else {
      res = c - 'a' + 10;
    }
  }
  return res;
}

void skipSpaces(char **sptr) {
  while (**sptr && isSpace(**sptr)) {
    (*sptr)++;
  }
}

long long s21_atoi(char *sptr) {
  int res = 0;
  int digit = 0;
  for (s21_size_t i = 0; i < s21_strlen(sptr); i++) {
    digit = sptr[i] - '0';
    res = (10 * res) + digit;
  }
  return res;
}

long double s21_atof(char **sptr, bool negative, int *width,
                     s21_size_t *numsCount) {
  long double res = 0.0;
  bool dot = false;
  if (**sptr != '.' && isBasedDigit(**sptr, 10)) {
    res += **sptr - '0';
    (*sptr)++;
    *numsCount = *numsCount + 1;
  }
  for (; **sptr && *width-- && (isBasedDigit(**sptr, 10) || **sptr == '.');
       (*sptr)++) {
    if (**sptr == '.') {
      dot = true;
      break;
    } else {
      *numsCount = *numsCount + 1;
      res = res * 10 + (**sptr - '0');
    }
  }
  int e = 0, eDot = 0;
  if (dot) {
    (*sptr)++;
    while (**sptr && *width-- && isBasedDigit(**sptr, 10)) {
      *numsCount = *numsCount + 1;
      res = res * 10 + (**sptr - '0');
      eDot--;
      (*sptr)++;
    }
  }
  isExp(sptr, &e, width);
  e = e + eDot;
  if (e > 0) {
    while (e != 0) {
      res *= 10;
      e--;
    }
  } else if (e < 0) {
    while (e != 0) {
      res /= 10;
      e++;
    }
  }
  return negative ? -res : res;
}
