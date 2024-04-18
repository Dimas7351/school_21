#ifndef GREP
#define GREP
#include <stdio.h>

typedef struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
  int f;
  int amount;
} flags;

void common(char* filename, char* pattern, flags* flag);
void manage_files(int argc, char** argv, flags* flag, char* pattern);

#endif
