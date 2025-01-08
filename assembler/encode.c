#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>


uint32_t encode_S_type(int opcode, int funct3, int rsrc, int imm, int rdst)
{
    printf(":: S type (opcode=%d funct3=%d args=[%d,%d,%d])\n",
           opcode, funct3, rsrc, rdst, imm);
    int imm_4_0  = (imm & 0b000000011111);
    int imm_11_5 = (imm & 0b111111100000) >> 5;
    return opcode | (imm_4_0 << 7) | (funct3 << 12) | (rdst << 15)
           | (rsrc << 20) | (imm_11_5 << 25);
}

uint32_t encode_B_type(int opcode, int funct3, int rsrc1, int rsrc2, int imm)
{
    printf(":: B type (opcode=%d funct3=%d args=[%d,%d,%d])\n",
           opcode, funct3, rsrc1, rsrc2, imm);
    int imm_4_1  = (imm & 0b0000000011110) >> 1;
    int imm_10_5 = (imm & 0b0011111100000) >> 5;
    int imm_11   = (imm & 0b0100000000000) >> 11;
    int imm_12   = (imm & 0b1000000000000) >> 12;
    return opcode | (imm_11 << 7) | (imm_4_1 << 8) | (funct3 << 12)
           | (rsrc1 << 15) | (rsrc2 << 20) | (imm_10_5 << 25)
           | (imm_12 << 31);
}

uint32_t encode_J_type(int opcode, int rdest, int imm)
{
    printf(":: J type (opcode=%d args=[%d,%d])\n",
        opcode, rdest, imm);
    int imm_10_1  = (imm & 0b000000000011111111110) >> 1;
    int imm_11    = (imm & 0b000000000100000000000) >> 11;
    int imm_19_12 = (imm & 0b011111111000000000000) >> 12;
    int imm_20    = (imm & 0b100000000000000000000) >> 20;
    return opcode | (rdest << 7) | (imm_19_12 << 12) | (imm_11 << 20)
           | (imm_10_1 << 21) | (imm_20 << 31);
}


//TODO : réaliser les fonctions pour les types I, et R

uint32_t encode_I_type(int opcode, int funct3, int rsrc1, int rdest, int imm){
  //TODO : implementer cette fonction 
}


uint32_t encode_R_type(int opcode, int funct3, int rsrc1, int rsrc2, int rdest, int imm){
  //TODO : implementer cette fonction
}


uint32_t encode_instruction(char* name, int arg1, int arg2, int arg3)
{
  // Cette fonction dispatche les instructions en regardant leur nom.

  // Exemple :
  if(!strcmp(name, "sd"))
    return encode_S_type(0b0100011, 0b011, arg1, arg2, arg3);

  //TODO : ajouter les autres instructions.
  // Attention à l'ordre des arguments.
  // Evidemment, on teste au fur et à mesure !
  
  
  printf(":: UNKNOWN INSTRUCTION\n");
  return 0;
}

