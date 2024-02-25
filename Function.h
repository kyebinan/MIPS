
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utility.h"

#ifndef __FUNCTION__
#define __FUNCTION__


void MFLO(char rd[],char Tab[35][10]);
void MFHI(char rd[],char Tab[35][10]);
void JR(char rd[],char Tab[35][10]);
void MULT(char rs[],char rt[],char Tab[35][10]);
void DIV(char rs[],char rt[],char Tab[35][10]);
void ADD(char rd[],char rs[],char rt[],char Tab[35][10]);
void SUB(char rd[],char rs[],char rt[],char Tab[35][10]);
void AND(char rd[],char rs[],char rt[],char Tab[35][10]);
void OR(char rd[],char rs[],char rt[],char Tab[35][10]);
void XOR(char rd[],char rs[],char rt[],char Tab[35][10]);
void SLT(char rd[],char rs[],char rt[],char Tab[35][10]);
void ROTR(char rd[],char rt[],char sa[],char Tab[35][10]);
void SLL(char rd[],char rt[],char sa[],char Tab[35][10]);
void SRL(char rd[],char rt[],char sa[],char Tab[35][10]);

void ADDI(char rt[],char rs[],char immediat[],char Tab[35][10]);
void LW(char rt[],char offset[],char base[],char Tab[35][10],char RAM[][4]);
void SW(char rt[],char offset[],char base[],char Tab[35][10],char RAM[][4]);
void LUI(char rt[],char immediat[],char Tab[35][10]);
void BEQ(char rs[],char rt[],char offset[],char Tab[35][10]);
void BNE(char rs[],char rt[],char offset[],char Tab[35][10]);
void BGTZ(char rs[],char offset[],char Tab[35][10]);
void BLEZ(char rs[],char offset[],char Tab[35][10]);

void Jump(char index[],char Tab[35][10]);
void JAL(char index[],char Tab[35][10]);

#endif


