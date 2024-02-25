#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryManagement.h"
#include "RegistryManagement.h"
#include "Utility.h"

#ifndef __HEXACONVERTE__
#define __HEXACONVERTE__

#define N 100 /*Array length*/
#define ERROR -1


enum TypeInstruction {R, I, J, NOP};
enum value {False, True};

void instructionExtraction(char *fileLine, char *instr);

int instructionType(char *instr);

void giveR_code(char function[]);
void R_instructionToHexa(char *instr, char hexa[]);

void giveI_code(char function[]);
void I_instructionToHexa(char *instr, char hexa[]);

void giveJ_code(char function[]);
void J_instructionToHexa(char *instr, char hexa[]);


void instructionToHexa(char *instr, char hexa[]);
void writeHexaFile(char *source,char *destination);

#endif