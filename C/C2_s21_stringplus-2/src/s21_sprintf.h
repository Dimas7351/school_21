#ifndef _SRC_S21_STRING_SPRINTF_H_
#define _SRC_S21_STRING_SPRINTF_H_

#include "s21_string.h"
typedef enum {
  NONE_L,
  SHORT_L,
  LONG_L,
  LONG_DOUBLE_L
} tlength;

typedef struct {
    bool PLUS_F;
    bool MINUS_F;
    bool SPACE_F;
    bool SHARP_F;
    bool NULL_F;
    bool ACCURACY;
} flags;
typedef struct Token{
    int Width;
    int Accuracy;
    char Spec;
    flags Flags;
    tlength LType;
} Token;

Token parseTokenSP(const char **format, va_list *args);
void parseFlags(Token *token, const char **format);
void parseWidth(Token *token, const char **format, va_list *args);
void parseAccurasy(Token *token, const char **format, va_list *args);
void parseLenght(Token *token, const char **format);
void parseSpec(Token *token, const char **format);
void handleTokenSP(Token token,  char **str, va_list args, char *strPtr);
void handleFlags(Token *token, char **buffer);
void handleAccuracy(Token *token, char **buffer);
void handleSciAccurracy(char **buffer, int accuracy);
void parseIntSP(Token *token, char **buffer, va_list args);
void parseUnsignedSP(Token *token, char **buffer, va_list args);
bool parseCharSP(Token *token, char **buffer, va_list args);
void parseStrSP(Token *token, char **buffer, va_list args);
void parsePointerSP(Token *token, char **buffer, va_list args);
void parseHexSP(Token *token, char **buffer, va_list args);
void parseOctalSP(Token *token, char **buffer, va_list args);
void parseFloatSP(Token *token, char **buffer, va_list args);
void parseExpSP(Token *token, char **buffer, va_list args);
void parseSciSP(Token *token, char **buffer, va_list args);
void charToBuffer(Token *token, char **buffer, va_list args);
void floatToBuffer(Token *token, long double num, char **buffer);
void numToBuffer(int64_t num, int base, char **buffer);
void unsignedToBuffer(uint64_t num, int base, char **buffer);
void expToBuffer(char **buffer, int sign, int e);
void removeNulls(Token *token, char **buffer);
void reverse(char **str);
void toUpperSP(char **str);
void toLowerSP(char **str);

#endif  //_SRC_S21_STRING_SPRINTF_H_