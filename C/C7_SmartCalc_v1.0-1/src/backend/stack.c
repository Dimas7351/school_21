#include "headers/stack.h"

rflag so_init(stack_op* stk) {
  if (!stk) return NULL_PTR;
  stk->head = NULL;
  stk->size = 0;
  return SUCCESS;
}

rflag so_node(node_o* src, token* tk) {
  if (!src) return FAILED_ALLOC;
  src->data = tk;
  src->next = NULL;
  return SUCCESS;
}

rflag so_push(stack_op* stk, token* tk) {
  if (!stk) return NULL_PTR;
  node_o* nnode = (node_o*)calloc(1, sizeof(node_o));
  rflag flag = so_node(nnode, tk);
  if (flag) return flag;
  nnode->next = stk->head;
  stk->head = nnode;
  stk->size++;
  return SUCCESS;
}

token* so_pop(stack_op* stk) {
  if (!stk) return NULL;
  token* res = stk->head->data;
  node_o* thead = stk->head;
  stk->head = stk->head->next;
  free(thead);
  stk->size--;
  return res;
}

rflag so_destroy(stack_op* stk) {
  if (!stk) return NULL_PTR;
  if (!stk->head) return NULL_PTR;
  node_o* curr = stk->head;
  node_o* next = NULL;
  do {
    next = curr->next;
    free(curr);
    curr = next;
    next = NULL;
  } while (curr);
  stk = NULL;
  return SUCCESS;
}

rflag sn_init(stack_num* stk) {
  if (!stk) return NULL_PTR;
  stk->head = NULL;
  stk->size = 0;
  return SUCCESS;
}

rflag sn_node(node_n* src, double val) {
  if (!src) return FAILED_ALLOC;
  src->data = val;
  src->next = NULL;
  return SUCCESS;
}

rflag sn_push(stack_num* stk, double val) {
  if (!stk) return NULL_PTR;
  node_n* nnode = (node_n*)calloc(1, sizeof(node_n));
  rflag flag = sn_node(nnode, val);
  if (flag) return flag;
  nnode->next = stk->head;
  stk->head = nnode;
  stk->size++;
  return SUCCESS;
}

double sn_pop(stack_num* stk) {
  double res = stk->head->data;
  node_n* thead = stk->head;
  stk->head = stk->head->next;
  free(thead);
  stk->size--;
  return res;
}

rflag sn_destroy(stack_num* stk) {
  if (!stk) return NULL_PTR;
  if (!stk->head) return NULL_PTR;
  node_n* curr = stk->head;
  node_n* next = NULL;
  do {
    next = curr->next;
    free(curr);
    curr = next;
    next = NULL;
  } while (curr);
  stk = NULL;
  return SUCCESS;
}
