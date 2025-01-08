#include <stdio.h>
#include <string.h>
#include "parse.h"
#include "utils.h"
#include "encode.h"

int main(int argc, char **argv)
{
    /* ./riscv-assembler <ASSEMBLER INPUT> <HEX OUTPUT> */
    if(argc != 3) {
        printf("usage: ./riscv-assembler <ASSEMBLER INPUT> <HEX OUTPUT>\n");
        return 1;
    }

    FILE *fp_in = fopen(argv[1], "r");
    if(fp_in == NULL) {
        perror("error: cannot read input file");
        return 1;
    }

    FILE *fp_out = fopen(argv[2], "w");
    if(fp_out == NULL) {
        perror("error: cannot open output file");
        return 1;
    }

    char ins[16], arg1[16], arg2[16], arg3[16];
    char *line = NULL;
    size_t n = 0;
    int lineno = 0;
    /* Lecture du fichier ligne-par-ligne */
    while(getline(&line, &n, fp_in) != -1) {
      long len = strlen(line);
      /* Permet de supprimer le caractère saut de ligne*/
      if (len > 0 && line[len - 1] == '\n') {
          line[len - 1] = '\0';
      }
      printf("Line #%d: [%s] (length %ld)\n", lineno, line, len);
      simplify_punct(line);
      remove_blanks(line);
      //printf("Line #%d: [%s] (length %ld)\n\n", lineno, line, len);
      if (strlen(line) == 0) {
            lineno++;
            continue;  // Sauter cette ligne et passer à la suivante
      }
      split_line(line, ins, arg1, arg2, arg3);
      printf("ins : %s, arg1 : %s, arg2 : %s, arg3 : %s\n\n", ins, arg1, arg2, arg3);
      lineno++;
    }

    free(line);
    
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
