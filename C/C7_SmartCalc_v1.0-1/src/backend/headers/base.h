#ifndef SRC_BASE_H_
#define SRC_BASE_H_

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Dummy numeric value to fill token with operator data.
 */
#define DUMMY_DOUBLE 22.0f / 7.0

/**
 * @brief Dummy character value to fill token with numerical data.
 */
#define DUMMY_CHAR 64

/**
 @brief Token structure for processing infix and postfix notation
 */
typedef struct {
  double num;
  char op;
  bool is_num;
} token;

/**
 @brief stack_op node structure. It stores token and a pointer to the next
 * node.
 */
typedef struct op_node {
  token* data;
  struct op_node* next;
} node_o;

/**
 @brief stack_num node structure. It stores token and a pointer to the next
 * node.
 */
typedef struct num_node {
  double data;
  struct num_node* next;
} node_n;

/**
 @brief stack_op (for operation) structure that stores stack size and pointer to
 the head (top)
 * node.
 */
typedef struct {
  int size;
  node_o* head;
} stack_op;

/**
 @brief stack_num (for numbers) structure that stores stack size and pointer to
 the head (top)
 * node.
 */
typedef struct {
  size_t size;
  node_n* head;
} stack_num;

/**
 * @brief Enum for coding math operators (mod, sqrt) and functions
 * (sin, cos, etc.).
 */
typedef enum {
  SIN = 's',
  COS = 'c',
  TAN = 't',
  ASIN = 'S',
  ACOS = 'C',
  ATAN = 'T',
  SQRT = 'q',
  LOG = 'l',
  LN = 'L',
  MOD = 'm',
} func_code;

/**
 * @brief Enum for handling different errors types.
 */
typedef enum {
  SUCCESS = 0,
  INVALID_TOKEN = 1,
  FAILED_CALC = 2,
  INVALID_STACK = 3,
  FAILED_ALLOC = 4,
  NULL_PTR = 5,
  INIT_ERROR = 6,
} rflag;

#endif  // SRC_BASE_H_
