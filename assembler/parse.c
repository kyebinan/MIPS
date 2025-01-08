#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


void replace_chars(char *str, char old_char, char new_char) {
    while (*str) {
        if (*str == old_char) {
            *str = new_char;
        }
        str++;
    }
}


void simplify_punct(char *str) {
    replace_chars(str, '(', ' ');
    replace_chars(str, ')', ' ');
    replace_chars(str, ',', ' ');
}


void remove_blanks(char *str) {
    int i = 0, j = 0;
    int length = strlen(str);

    while (isspace((unsigned char)str[i])) {
        i++;
    }

    while (i < length) {
        if (isspace((unsigned char)str[i])) {
            if (j > 0 && !isspace((unsigned char)str[j - 1])) {
                str[j++] = ' ';
            }
        } else {
            str[j++] = str[i];
        }
        i++;
    }

    str[j] = '\0';
}

bool is_comment(const char *str) {
    while (*str == ' ' || *str == '\t') {  
        str++;
    }
    return (*str == '#');  
}


bool split_line(const char *str, char *ins, char *arg1, char *arg2, char *arg3) {
  strcpy(ins, "");
  strcpy(arg1, "");
  strcpy(arg2, "");
  strcpy(arg3, "");

  if (is_comment(str) || strcmp(str, "") == 0) {
        return false;
  }

  sscanf(str, "%s%s%s%s", ins, arg1, arg2, arg3);
  return true;
}

