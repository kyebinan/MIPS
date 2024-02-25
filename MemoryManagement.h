#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utility.h"

#ifndef __MEMORYMANAGEMENT__
#define __MEMORYMANAGEMENT__

#define nbOctets 16777217

//typedef char memory[nbOctets][3] ;

void loadByte(int adr,char RAM[][4],char content[]);
void storeByte(int adr,char RAM[][4],char content[]);

void loadWord(int adr,char RAM[][4],char content[]);
void storeWord(int adr,char RAM[][4],char content[]);

#endif