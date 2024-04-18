#include <stdio.h>
#include <string.h>

void empty(FILE* f) {
  char c;
  while ((c = fgetc(f)) != EOF) {
    printf("%c", c);
  }
}

void b(FILE* f) {
  char s[4096];
  int score = 0;
  while (!feof(f)) {
    strcpy(s, "");
    fgets(s, 4096, f);
    if (s[0] == '\n') {
      printf("\n");
    } else if (s[0] != '\0') {
      score++;
      printf("%6i\t%s", score, s);
    }
  }
}

void n(FILE* f) {
  char s[4096];
  int score = 0;
  while (!feof(f)) {
    strcpy(s, "");
    fgets(s, 4096, f);
    score++;
    if (s[0] != '\0') printf("%6i\t%s", score, s);
  }
}

void s(FILE* f) {
  char s[10000];
  int i = 0;
  while (!feof(f)) {
    s[i] = fgetc(f);
    i++;
  }
  for (int j = 0; j < i; j++) {
    if (s[j] == '\n' && s[j + 1] == '\n' && s[j + 2] == '\n') continue;
    if ((int)s[j] != -1) printf("%c", s[j]);
  }
}

void et(FILE* f, int flag, int end) {
  char c;
  while ((c = fgetc(f)) != EOF) {
    int ch = (int)c;
    if (c == '\n' && end == 1) putchar('$');
    if (flag == 0)
      putchar(c);
    else {
      if (ch == 127) {
        putchar('^');
        putchar('?');
      } else if (ch == 10) {
        putchar('\n');
      } else if (ch == 9 && end == 1) {
        putchar('\t');
      } else if (ch < 32) {
        putchar('^');
        ch += 64;
        printf("%c", ch);
      } else
        putchar(c);
    }
  }
}

int main(int argc, char** argv) {
  FILE* f;
  int flag = 0, end = 0, i = 1;
  if (argc > i) {
    if (argc == i + 1) {
      f = fopen(argv[i], "r+");
      if (f == NULL)
        printf("No such file or directory\n");
      else {
        empty(f);
        fclose(f);
      }
    } else {
      f = fopen(argv[i + 1], "r+");
      if (f == NULL)
        printf("No such file or directory\n");
      else {
        if ((strcmp(argv[1], "-b") == 0) ||
            (strcmp(argv[1], "--number-nonblank") == 0))
          b(f);
        else if (strcmp(argv[1], "-e") == 0) {
          flag = 1;
          end = 1;
          et(f, flag, end);
        } else if (strcmp(argv[1], "-E") == 0) {
          end = 1;
          et(f, flag, end);
        } else if (strcmp(argv[1], "-n") == 0 ||
                   (strcmp(argv[1], "--number") == 0))
          n(f);
        else if (strcmp(argv[1], "-s") == 0 ||
                 (strcmp(argv[1], "--squeze-blank") == 0))
          s(f);
        else if (strcmp(argv[1], "-t") == 0) {
          flag = 1;
          et(f, flag, end);
        } else if (strcmp(argv[1], "-T") == 0)
          et(f, flag, end);
        fclose(f);
      }
    }
  }
}
