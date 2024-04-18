#include "headers/calc.h"

rflag calculate(char *infix, double x, double *ans) {
  int ilength = 0;
  int plength = 0;
  token *infix_tokens = get_tokens(infix, &ilength);
  token *postfix_tokens = NULL;
  rflag flag = SUCCESS;
  if (infix_tokens) {
    postfix_tokens = get_postfix(infix_tokens, ilength, &plength);
    if (postfix_tokens) {
      flag = calc(postfix_tokens, plength, ans, x);
      free(postfix_tokens);
    } else
      flag = INVALID_STACK;
    free(infix_tokens);
  } else
    flag = INVALID_TOKEN;
  return flag;
}

rflag calc(token *postfix_tokens, int plength, double *ans, double x) {
  stack_num stk = {0};
  sn_init(&stk);
  rflag flag = SUCCESS;
  for (int i = 0; i < plength && flag == SUCCESS; i++) {
    if (postfix_tokens[i].is_num) {
      sn_push(&stk, postfix_tokens[i].num);
    } else {
      hard_op(&stk, postfix_tokens[i].op, &flag);
      simple_op(&stk, postfix_tokens[i].op, x, &flag);
    }
  }
  if (stk.size != 1)
    flag = FAILED_CALC;
  else {
    *ans = sn_pop(&stk);
    if (fabs(*ans) < EPS) *ans = 0;
  }
  sn_destroy(&stk);
  return flag;
}

void simple_op(stack_num *stk, char operation, double x, rflag *flag) {
  switch (operation) {
    case 'x':
      sn_push(stk, x);
      break;
    case '+':
      op_result(stk, flag, operation);
      break;
    case '*':
      op_result(stk, flag, operation);
      break;
    case '-':
      op_result(stk, flag, operation);
      break;
    case '/':
      op_result(stk, flag, operation);
      break;
    case 'm':
      op_result(stk, flag, operation);
      break;
    case '^':
      op_result(stk, flag, operation);
      break;
  }
}

void hard_op(stack_num *stk, char operation, rflag *flag) {
  switch (operation) {
    case SIN:
      op_result(stk, flag, operation);
      break;
    case COS:
      op_result(stk, flag, operation);
      break;
    case TAN:
      op_result(stk, flag, operation);
      break;
    case ASIN:
      op_result(stk, flag, operation);
      break;
    case ACOS:
      op_result(stk, flag, operation);
      break;
    case ATAN:
      op_result(stk, flag, operation);
      break;
    case SQRT:
      op_result(stk, flag, operation);
      break;
    case LOG:
      op_result(stk, flag, operation);
      break;
    case LN:
      op_result(stk, flag, operation);
      break;
  }
}

void op_result(stack_num *stk, rflag *flag, char operation) {
  double top = 0.0;
  switch (operation) {
    case '+': {
      if (stk_valid(stk))
        sn_push(stk, sn_pop(stk) + sn_pop(stk));
      else
        *flag = INVALID_STACK;
      break;
    }
    case '*': {
      if (stk_valid(stk))
        sn_push(stk, sn_pop(stk) * sn_pop(stk));
      else
        *flag = INVALID_STACK;
      break;
    }
    case '-': {
      if (stk_valid(stk)) {
        top = sn_pop(stk);
        sn_push(stk, sn_pop(stk) - top);
      } else
        *flag = INVALID_STACK;
      break;
    }
    case '/': {
      if (stk_valid(stk)) {
        top = sn_pop(stk);
        if (fabs(top) >= EPS)
          sn_push(stk, sn_pop(stk) / top);
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_STACK;
      break;
    }
    case 'm': {
      if (stk_valid(stk)) {
        top = sn_pop(stk);
        if (fabs(top) >= EPS)
          sn_push(stk, fmod(sn_pop(stk), top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_STACK;
      break;
    }
    case '^': {
      if (stk_valid(stk)) {
        top = sn_pop(stk);
        sn_push(stk, powl(sn_pop(stk), top));
      }
      break;
    }
    case SIN: {
      if (stk->head)
        sn_push(stk, sin(sn_pop(stk)));
      else
        *flag = INVALID_STACK;
      break;
    }
    case COS: {
      if (stk->head)
        sn_push(stk, cos(sn_pop(stk)));
      else
        *flag = INVALID_STACK;
      break;
    }
    case TAN: {
      if (stk->head) {
        top = sn_pop(stk);
        if (fabs(cos(top)) >= EPS)
          sn_push(stk, tan(top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_STACK;
      break;
    }
    case ASIN: {
      if (stk->head)
        sn_push(stk, asin(sn_pop(stk)));
      else
        *flag = INVALID_STACK;
      break;
    }
    case ACOS: {
      if (stk->head)
        sn_push(stk, acos(sn_pop(stk)));
      else
        *flag = INVALID_STACK;
      break;
    }
    case ATAN: {
      if (stk->head)
        sn_push(stk, atan(sn_pop(stk)));
      else
        *flag = INVALID_STACK;
      break;
    }
    case SQRT: {
      if (stk->head) {
        top = sn_pop(stk);
        if (top >= 0)
          sn_push(stk, sqrt(top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_STACK;
      break;
    }
    case LOG: {
      if (stk->head) {
        top = sn_pop(stk);
        if (top > EPS)
          sn_push(stk, log10(top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_STACK;
      break;
    }
    case LN: {
      if (stk->head) {
        top = sn_pop(stk);
        if (top > EPS)
          sn_push(stk, log(top));
        else
          *flag = FAILED_CALC;
      } else
        *flag = INVALID_STACK;
      break;
    }
  }
}

bool stk_valid(stack_num *stk) { return stk->head && stk->head->next; }
