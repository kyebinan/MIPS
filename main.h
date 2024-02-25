#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryManagement.h"
#include "RegistryManagement.h"
#include "Utility.h"
#include "Function.h"

#ifndef __MAIN__
#define __MAIN__
//#define N 100 /*Array length*/
//enum TypeInstruction {R, I, J, NOP};
//enum value {False, True};

void R_instructionExecute(char *instr,char Tab[35][10]);
void I_instructionExecute(char *instr,char Tab[35][10],char RAM[][4]);
void J_instructionExecute(char *instr,char Tab[35][10]);
void instructionExecution(char *instr,char Tab[35][10],char RAM[][4]);
void executeFile(char *source,char *destination,char Tab[35][10],char RAM[][4],char RAMinst[200][100]);
void executeFilePasAPas(char *source,char *destination,char Tab[35][10],char RAM[][4],char RAMinst[200][100]);
void afficheRegistre(char Tab[35][10]);
void initRegistre(char Tab[35][10]);
void afficheRam(char RAM[100][4]);
void initRam(char RAM[100][4]);
void initRegistre0(char Tab[35][10]);
#endif 