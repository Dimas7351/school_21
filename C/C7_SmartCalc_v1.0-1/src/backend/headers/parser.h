#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include "base.h"
#include "stack.h"

/**
 @brief Converts infix notation (1 + 2) into postfix notation (1 2 +)
 */
token* get_postfix(token* infix, int ilength, int* plength);

/**
 @brief Create array of tokens
 */
token* get_tokens(const char* equation, int* length);

/**
 @brief Checks if given char is an operand
 */
bool is_op(const char chr);

/**
 @brief Checks if given char is a dot
 */
bool is_dot(const char chr);

/**
 @brief Checks if given char is a number
 */
bool is_num(const char chr);

/**
 @brief Checks if given func_name is a mod function
 */
bool is_mod(const char* func_name);

/**
 @brief Converts given char* to lowercase
 */
char* to_low(char* src);

/**
 @brief Write given operation to tokens array
 */
void write_op_token(token* curr_token, char operation, int* curr_equation_idx,
                    int shift);

/**
 @brief Writes new token tokens array and shifts current equation index by given
 value
 */
void oshift(token* curr_token, char operation, int* num_tokens,
            int* curr_equation_idx, int shift);

/**
 @brief Convert string to double
 */
bool to_double(const char* snum, double* num, int* curr_equation_idx);

/**
 @brief Checks if given func_name is an actual function name
 */
bool is_function(const char* src, const char* func_name, int* shift);

/**
 @brief Checks the operation priority
 */
int get_prior(token* tk);

/**
 @brief Compares two operations priority difference
 */
int diff_prior(token* ltk, token* rtk);

#endif  // SRC_PARSER_PARSER_H_
