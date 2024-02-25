#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef __UTILITY__
#define __UTILITY__

void checkRegisters(char regist[]);
void decimalToBinary(char ch[], int nbit);
void decimalToBinarySigned(char ch[], int nbit);
void binaryToHexa(char bin[], char hexa[]);
int hexaToDecimal(char hexa[]);
void hexaToBinary(char hexa[],char bin[]);
int hexaSignedToDecimal(char hexa[]);


#endif