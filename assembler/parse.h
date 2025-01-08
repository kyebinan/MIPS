#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void replace_chars(char *str, char old_char, char new_char);

void simplify_punct(char *str);

void remove_blanks(char *str);

bool is_comment(const char *str);

bool split_line(const char *str, char *ins, char *arg1, char *arg2, char *arg3);

#endif // PARSER_H

