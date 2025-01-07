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
    // ...

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
