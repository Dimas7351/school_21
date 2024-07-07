#ifndef _SRC_S21_STRING_SSCANF_H_
#define _SRC_S21_STRING_SSCANF_H_

#include "s21_string.h"
typedef enum twidth { 
    NONE_W,
    NUMBER_W,
    ASTERIKS_W
} twidth;

typedef enum tlength {
  NONE_L,
  SHORT_L,
  LONG_L,
  LONG_LONG_L,
  DOUBLE_L,
  LONG_DOUBLE_L
} tlength;

typedef struct Token {
    int width;
    twidth widthType;
    tlength lenght;
    char spec;
} Token;

//main = ibm.com/docs/en/zos/2.1.0?topic=programs-sscanf-read-format-data
Token parseToken(char **fptr, char **sptr);
void parseW(Token *token, char **fptr);
void parseL(Token *token, char **fptr);
bool handleToken(Token token, char **sptr, va_list arg, int *res, s21_size_t start);
void handleSpaceSpec(char **sptr);
void handlePercentSpec(char **sptr);
int handleIntSpec(Token token, va_list args, char **sptr);
int handlePSpec(Token token, va_list args, char **sptr);
int handleCSSpec(Token token, va_list args, char **sptr);
int handleEefGgSpec(Token token, va_list args, char **sptr);
int handleISpec(Token token, va_list args, char **sptr);
int handleXxSpec(Token token, va_list args, char **sptr);
int handleOSpec(Token token, va_list args, char **sptr);
int handleUInt(Token token, va_list args, char **sptr, int base, bool n);
int handleCount(va_list args, char **sptr, s21_size_t start);
int parseStr(Token token, char **sptr, va_list args);
int parseInt(Token token, char **sptr, long long *var);
int parseUint(Token token, char **sptr, unsigned long long *dest, int base, bool negative);
int parseHex(Token token, va_list args, char **sptr);
int parseOctal(Token token, va_list args, char **sptr);
int parseFloat(Token token, char **sptr, long double *res);
int isEOF(const char *sptr);
bool isNANINF(char **sptr, bool negative, long double *dest);
bool isExp(char **sptr, int *e, int *width);
bool isSpace(char c);
void isNegative(bool *neg, int *width, char **sptr);
void skipSpaces(char **sptr);
unsigned long fromBasedDigit(char c, int base);
long double s21_atof(char **sptr, bool negative, int *width, s21_size_t *numsCount);

#endif  //_SRC_S21_STRING_SSCANF_H_