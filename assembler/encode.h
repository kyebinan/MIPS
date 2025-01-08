#ifndef ENCODE_H
#define ENCODE_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>


uint32_t encode_S_type(int opcode, int funct3, int rsrc, int imm, int rdst);

uint32_t encode_B_type(int opcode, int funct3, int rsrc1, int rsrc2, int imm);

uint32_t encode_J_type(int opcode, int rdest, int imm);

uint32_t encode_I_type(int opcode, int funct3, int rsrc1, int rdest, int imm);

uint32_t encode_R_type(int opcode, int funct3, int rsrc1, int rsrc2, int rdest, int imm);

uint32_t encode_instruction(char* name, int arg1, int arg2, int arg3);

#endif // ENCODE_H
