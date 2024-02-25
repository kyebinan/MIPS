#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryManagement.h"
#include "Utility.h"


void loadByte(int adr,char RAM[][4],char content[]){
	int i;
	for(i = 0;i < 2; i++)content[i] = RAM[adr][i];
}

void storeByte(int adr,char RAM[][4],char content[]){
	int i;
	for(i = 0;i < 2;i++)RAM[adr][i]= content[i];
}

void loadWord(int adr,char RAM[][4],char content[]){
	int i,j,k=0;
	for(i = adr; i < adr+4 ; i++){
		for(j = 0; j < 2; j++,k++)content[k] = RAM[i][j];
	} 
}

void storeWord(int adr,char RAM[][4],char content[]){
	int i,j,k=0;
	for(i = adr; i < adr+4 ; i++){
		for(j = 0; j < 2; j++,k++) RAM[i][j]=content[k];
	} 			
}
