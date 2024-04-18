#include "headers/parser.h"

bool is_dot(const char chr) { return chr == '.'; }

bool is_operand(const char chr) {
  return chr == '/' || chr == '*' || chr == '-' || chr == '+' || chr == '(' ||
         chr == ')' || chr == 's' || chr == 'S' || chr == 't' || chr == 'c' ||
         chr == 'C' || chr == 'q' || chr == 'l' || chr == 'L' || chr == 'm' ||
         chr == 'T';
}

bool is_num(const char chr) { return chr >= '0' && chr <= '9'; }

bool is_mod(const char *func_name) { return !strncmp(func_name, "mod", 3); }

char *to_low(char *src) {
  int length = strlen(src);
  char *result = (char *)malloc((length * sizeof(char)) + 1);
  if (!result) return NULL;

  for (int i = 0; i < length; i++) {
    result[i] = src[i];
    if (result[i] >= 'A' && result[i] <= 'Z') result[i] += 'a' - 'A';
  }
  result[length] = '\0';
  return result;
}

void write_op_token(token *curr_token, char operation, int *curr_equation_idx,
                    int shift) {
  curr_token->num = DUMMY_DOUBLE;
  curr_token->op = operation;
  curr_token->is_num = false;

  (*curr_equation_idx) += shift;
}

void oshift(token *curr_token, char operation, int *num_tokens,
            int *curr_equation_idx, int shift) {
  write_op_token(curr_token, operation, curr_equation_idx, shift);
  (*num_tokens)++;
}

bool to_double(const char *snum, double *num, int *curr_equation_idx) {
  while (snum[*curr_equation_idx] >= '0' && snum[*curr_equation_idx] <= '9') {
    *num = *num * 10 + (snum[*curr_equation_idx] - '0');
    (*curr_equation_idx)++;
  }
  int mant_size = 0;
  double mantissa = 0.0;
  if (is_dot(snum[*curr_equation_idx])) {
    (*curr_equation_idx)++;
    if (snum[*curr_equation_idx] == ' ')
      return true;
    else if (snum[*curr_equation_idx] < '0' || snum[*curr_equation_idx] > '9')
      return false;

    while (snum[*curr_equation_idx] >= '0' && snum[*curr_equation_idx] <= '9') {
      mantissa = mantissa * 10 + (snum[*curr_equation_idx] - '0');
      (*curr_equation_idx)++;
      mant_size++;
    }
  }
  for (; mant_size > 0; mant_size--) mantissa /= 10;
  *num += mantissa;
  return true;
}

bool is_function(const char *src, const char *func_name, int *shift) {
  int length = 0;
  bool flag = true;
  while (flag && func_name[length]) {
    if (src[length] == '\0')
      flag = false;
    else if (src[length] != func_name[length])
      flag = false;
    length++;
  }
  if (flag && src[length] != '(' && strcmp(func_name, "mod")) flag = false;
  *shift = length;
  return flag;
}

int get_prior(token *tk) {
  int res = 0;
  switch (tk->op) {
    case '(':
    case ')':
      break;
    case '+':
    case '-':
      res = 2;
      break;
    case '*':
    case '/':
    case MOD:
      res = 3;
      break;
    case '^':
    case SIN:
    case COS:
    case TAN:
    case ASIN:
    case ACOS:
    case ATAN:
    case SQRT:
    case LOG:
    case LN:
      res = 4;
      break;
  }
  return res;
}

int diff_prior(token *ltk, token *rtk) {
  return get_prior(ltk) - get_prior(rtk);
}

token *get_postfix(token *infix, int ilength, int *plength) {
  stack_op stk = {0};
  if (so_init(&stk)) return NULL;
  token *postfix = (token *)calloc(2 * ilength, sizeof(token));
  *plength = 0;
  int idx = 0;
  token *tmp = NULL;
  while (idx < ilength) {
    if (infix[idx].is_num) {
      postfix[*plength].num = infix[idx].num;
      postfix[*plength].op = DUMMY_CHAR;
      postfix[*plength].is_num = true;

      (*plength)++;
      idx++;
    } else if (infix[idx].op == 'x') {
      postfix[*plength].op = infix[idx].op;
      postfix[*plength].num = 0.0;
      postfix[*plength].is_num = false;

      (*plength)++;
      idx++;
    } else {
      if (infix[idx].op == '(') {
        rflag flag = so_push(&stk, &infix[idx]);
        if (flag) return NULL;
        idx++;
      } else if (infix[idx].op == ')') {
        tmp = so_pop(&stk);
        while (tmp->op != '(') {
          postfix[*plength].op = tmp->op;
          postfix[*plength].num = DUMMY_DOUBLE;
          postfix[*plength].is_num = false;

          (*plength)++;
          tmp = so_pop(&stk);
        }
        idx++;
      } else {
        if (stk.head && diff_prior(stk.head->data, &infix[idx]) >= 0) {
          tmp = so_pop(&stk);
          postfix[*plength].op = tmp->op;
          postfix[*plength].num = DUMMY_DOUBLE;
          postfix[*plength].is_num = false;

          (*plength)++;
        } else {
          so_push(&stk, &infix[idx]);
          idx++;
        }
      }
    }
  }
  while (stk.size) {
    tmp = so_pop(&stk);
    postfix[*plength].op = tmp->op;
    postfix[*plength].num = DUMMY_DOUBLE;
    postfix[*plength].is_num = false;

    (*plength)++;
  }
  so_destroy(&stk);
  return postfix;
}

token *get_tokens(const char *equation, int *num_tokens) {
  token *tokens = (token *)calloc(strlen(equation) * 2, sizeof(token));
  if (!tokens) return NULL;
  double number = 0.0;
  int cnt_brackets = 0;
  int shift = 0;
  int idx = 0;
  bool flag = true;
  *num_tokens = 0;
  while (flag && equation[idx]) {
    number = 0.0;
    shift = 0;
    switch (equation[idx]) {
      case ' ':
        idx++;
        break;
      case '+':
      case '*':
      case '/':
      case '^':
        oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
        break;
      case '-': {
        if (*num_tokens == 0 ||
            (*num_tokens && tokens[*num_tokens - 1].op == '(') ||
            (idx && equation[idx - 1] == ' ' && equation[idx + 1] != ' ')) {
          tokens[*num_tokens].is_num = true;
          tokens[*num_tokens].num = 0.0;
          tokens[*num_tokens].op = DUMMY_CHAR;
          (*num_tokens)++;
        }
        oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
        break;
      }
      case '(':
        oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
        cnt_brackets++;
        break;
      case ')':
        oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
        cnt_brackets--;
        break;
      case 'a': {
        if (is_function(equation + idx, "asin", &shift)) {
          oshift(&(tokens[*num_tokens]), ASIN, num_tokens, &idx, shift);
        } else if (is_function(equation + idx, "acos", &shift)) {
          oshift(&(tokens[*num_tokens]), ACOS, num_tokens, &idx, shift);
        } else if (is_function(equation + idx, "atan", &shift)) {
          oshift(&(tokens[*num_tokens]), ATAN, num_tokens, &idx, shift);
        } else
          flag = false;
        break;
      }
      case 's': {
        if (is_function(equation + idx, "sin", &shift)) {
          oshift(&(tokens[*num_tokens]), SIN, num_tokens, &idx, shift);
        } else if (is_function(equation + idx, "sqrt", &shift)) {
          oshift(&(tokens[*num_tokens]), SQRT, num_tokens, &idx, shift);
        } else
          flag = false;
        break;
      }
      case 'l': {
        if (is_function(equation + idx, "log", &shift)) {
          oshift(&(tokens[*num_tokens]), LOG, num_tokens, &idx, shift);
        } else if (is_function(equation + idx, "ln", &shift)) {
          oshift(&(tokens[*num_tokens]), LN, num_tokens, &idx, shift);
        } else
          flag = false;
        break;
      }
      case 'c': {
        if (is_function(equation + idx, "cos", &shift)) {
          oshift(&(tokens[*num_tokens]), COS, num_tokens, &idx, shift);
        } else
          flag = false;
        break;
      }
      case 't': {
        if (is_function(equation + idx, "tan", &shift)) {
          oshift(&(tokens[*num_tokens]), TAN, num_tokens, &idx, shift);
        } else
          flag = false;
        break;
      }
      case 'm': {
        if (is_function(equation + idx, "mod", &shift)) {
          oshift(&(tokens[*num_tokens]), MOD, num_tokens, &idx, shift);
        } else
          flag = false;
        break;
      }
      case 'x': {
        if (*num_tokens && tokens[(*num_tokens) - 1].is_num) {
          tokens[*num_tokens].is_num = false;
          tokens[*num_tokens].num = DUMMY_DOUBLE;
          tokens[*num_tokens].op = '*';

          (*num_tokens)++;
        }
        oshift(&(tokens[*num_tokens]), equation[idx], num_tokens, &idx, 1);
        break;
      }
      default: {
        if (equation[idx] >= '0' && equation[idx] <= '9') {
          if (!to_double(equation, &number, &idx))
            flag = false;
          else {
            tokens[*num_tokens].is_num = true;
            tokens[*num_tokens].num = number;
            tokens[*num_tokens].op = DUMMY_CHAR;
            (*num_tokens)++;
          }
        } else {
          flag = false;
        }
        break;
      }
    }
  }
  if (cnt_brackets || !flag) {
    if (tokens) free(tokens);
    tokens = NULL;
  }
  return tokens;
}
