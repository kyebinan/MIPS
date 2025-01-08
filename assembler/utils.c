#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_line_by_line(FILE *fp)
{
    char *line = NULL;
    size_t n = 0;
    int lineno = 0;
    /* Lecture du fichier ligne-par-ligne */
    while(getline(&line, &n, fp) != -1) {
      long len = strlen(line);
      /* Permet de supprimer le caractère saut de ligne*/
      if (len > 0 && line[len - 1] == '\n') {
          line[len - 1] = '\0';
      }
      printf("Line #%d: [%s] (length %ld)\n", lineno, line, len);
      lineno++;
    }

    free(line);
}
