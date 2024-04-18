#include "base.h"

/**
 @brief Initializes stack_op object
 */
rflag so_init(stack_op* stk);

/**
 @brief Initializes node_o object with given token values
 */
rflag so_node(node_o* src, token* tk);

/**
 @brief Pushes new token onto the stack
 */
rflag so_push(stack_op* stk, token* tk);

/**
 @brief Pops value from stack and returns its value
 */
token* so_pop(stack_op* stk);

/**
 @brief Destroys stack object
 */
rflag so_destroy(stack_op* stk);

/**
 @brief Initializes stack_num object
 */
rflag sn_init(stack_num* stk);

/**
 @brief Initializes node_n object with given token values
 */
rflag sn_node(node_n* src, double val);

/**
 @brief Pushes new token onto the stack
 */
rflag sn_push(stack_num* stk, double val);

/**
 @brief Pops value from stack and returns its value
 */
double sn_pop(stack_num* stk);

/**
 @brief Destroys stack object
 */
rflag sn_destroy(stack_num* stk);
