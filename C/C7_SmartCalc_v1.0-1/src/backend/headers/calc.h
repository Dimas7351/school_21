#ifndef SRC_CALC_CALC_H_
#define SRC_CALC_CALC_H_

#define EPS 1E-6
#define PI 3.14159265358979323846

#include "base.h"
#include "parser.h"
#include "stack.h"

/**
 @brief Calculates given expression with Reverse Polish Notation (RPN)
 */
rflag calculate(char* infix, double x, double* ans);

/**
 @brief Runs calculation on given postfix notation equation
 */
rflag calc(token* postfix_tokens, int plength, double* ans, double x);

/**
 @brief Runs calculation on arithmetic operations ('+', '-', 'mod', etc.)
 */
void simple_op(stack_num* stk, char operation, double x, rflag* flag);

/**
 @brief Runs calculation on arithmetic operations (sin(x), cos, etc.)
 */
void hard_op(stack_num* stk, char operation, rflag* flag);

/**
 @brief Performs given operation and pushes result onto the stack
 */
void op_result(stack_num* stk, rflag* flag, char operation);

/**
 @brief Checks if there are at least two double values in the stack
 */
bool stk_valid(stack_num* stk);

#endif  // SRC_CALC_CALC_H_
