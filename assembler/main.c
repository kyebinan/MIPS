#include <stdio.h>
#include <string.h>

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

    // TODO : Lire depuis fp_in, écrire les instructions assemblées dans fp_out
    char *line = NULL;
    size_t n = 0;
    int lineno = 0;
    /* Lecture du fichier ligne-par-ligne */
    while(getline(&line, &n, fp_in) != -1) {
        printf("Line #%d: [%s] (length %ld)\n", lineno, line, strlen(line));
        lineno++;
        //TODO faire les traitement qui s'imposent pour génerer l'assembleur
        
    
        //TODO faire les traitement qui s'imposent pour prendre en compte les étiquettes
        

        //TODO faire les traitement qui s'imposent pour prendre en compte les directives
    }

    free(line);

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
