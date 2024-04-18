#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void common(char* filename, char* pattern, flags* flag) {
  regex_t regex;
  regmatch_t matches[100];
  char s[4096];
  int reti, score_lines = 0, line_number = 0, file_flag = 0;
  FILE* f = fopen(filename, "r+");
  if (f == NULL && flag->s == 0)
    printf("No such file or directory");
  else if (f != NULL) {
    if (flag->i == 0)
      reti = regcomp(&regex, pattern, REG_NEWLINE);
    else
      reti = regcomp(&regex, pattern, REG_ICASE | REG_NEWLINE);
    while (!feof(f)) {
      reti = 0;
      strcpy(s, "");
      fgets(s, 4096, f);

      if (flag->o == 1) {
        char* string_ptr = s;
        while ((reti = regexec(&regex, string_ptr,
                               sizeof(matches) / sizeof(matches[0]), matches,
                               0)) == 0) {
          if (flag->amount == 1)
            printf("%s:%s\n", filename, pattern);
          else
            printf("%s\n", pattern);
          string_ptr += matches[0].rm_eo;
        }
      } else {
        reti = regexec(&regex, s, 0, NULL, 0);
        line_number++;
        if (flag->v == 1) {
          if (reti != 0) {
            if (flag->amount == 1)
              printf("%s:%s", filename, s);
            else
              printf("%s", s);
          }
        } else {
          if (reti == 0) {
            file_flag = 1;
            score_lines++;
            if (flag->h) {
              printf("%s", s);
            }
            if (flag->amount == 1) {
              if (flag->n == 1)
                printf("%s:%d:%s", filename, line_number, s);
              else if (flag->i == 1 || flag->e == 1 || flag->s == 1 ||
                       flag->o == 1) {
                if (flag->o == 1)
                  printf("%s:%s\n", filename, pattern);
                else
                  printf("%s:%s", filename, s);
              }
            } else {
              if (flag->n == 1)
                printf("%d:%s", line_number, s);
              else if (flag->i == 1 || flag->e == 1 || flag->s == 1 ||
                       flag->o == 1) {
                if (flag->o == 1)
                  printf("%s\n", pattern);
                else
                  printf("%s", s);
              }
            }
          }
        }
      }
    }
    if (flag->c == 1) {
      if (flag->amount == 1)
        printf("%s:%d\n", filename, score_lines);
      else
        printf("%d\n", score_lines);
    }

    if (flag->l == 1) {
      if (file_flag) printf("%s\n", filename);
    }

    if (s[0] != '\0' &&
        ((flag->v == 1 && reti != 0) ||
         ((flag->e == 1 || flag->i == 1 || flag->s == 1) && reti == 0)))
      printf("\n");
    fclose(f);
    regfree(&regex);
  }
}

void grep_f(char* filename1, char* filename2) {
  FILE* file1 = fopen(filename1, "r");
  FILE* file2 = fopen(filename2, "r");

  if (file1 == NULL || file2 == NULL) {
    printf("No such file or directory\n");
    return;
  }

  char pattern[4096];
  regex_t regex;
  int reti;
  int line_printed[10000] = {0};
  while (fgets(pattern, sizeof(pattern), file1) != NULL) {
    pattern[strcspn(pattern, "\n")] = '\0';
    reti = regcomp(&regex, pattern, 0);
    if (reti != 0) {
      printf("Error compiling regex: %s\n", pattern);
      continue;
    }

    char line[4096];
    int line_number = 0;
    while (fgets(line, sizeof(line), file2) != NULL) {
      line_number++;

      if (line_printed[line_number] == 1) {
        continue;
      }

      if (regexec(&regex, line, 0, NULL, 0) == 0) {
        printf("%s", line);
        line_printed[line_number] = 1;
      }
    }
    regfree(&regex);
    rewind(file2);
  }

  fclose(file1);
  fclose(file2);
}

void manage_files(int argc, char** argv, flags* flag, char* pattern) {
  char* file_names[argc - 3];

  for (int i = 3; i < argc; i++) {
    file_names[i - 3] = argv[i];
  }
  for (int j = 0; j < argc - 3; j++) {
    common(file_names[j], pattern, flag);
  }
}

int main(int argc, char* argv[]) {
  int option;
  flags* flag = malloc(sizeof(flags));
  char pattern[4096];
  flag->e = flag->c = flag->v = flag->i = flag->l = flag->n = flag->h =
      flag->s = flag->amount = flag->o = flag->f = 0;
  if (argc > 2) {
    strcpy(pattern, argv[2]);

    while ((option = getopt_long(argc, argv, "ecvilnhsfo:", NULL, NULL)) !=
           -1) {
      switch (option) {
        case 'e':
          flag->e = 1;
          break;
        case 'c':
          flag->c = 1;
          break;
        case 'v':
          flag->v = 1;
          break;
        case 'i':
          flag->i = 1;
          break;
        case 'l':
          flag->l = 1;
          break;
        case 'n':
          flag->n = 1;
          break;
        case 'h':
          flag->h = 1;
          break;
        case 'o':
          flag->o = 1;
          break;
        case 'f':
          flag->f = 1;
          break;
        case 's':
          flag->s = 1;
          break;
          return 1;
      }
    }
    if (argc > 4) {
      flag->amount = 1;
    }

    if (flag->f == 1)
      grep_f(argv[2], argv[3]);
    else
      manage_files(argc, argv, flag, pattern);
  }

  free(flag);
  return 0;
}
