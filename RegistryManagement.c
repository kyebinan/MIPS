#include "RegistryManagement.h"
#include "Utility.h"


void loadRegister(char regist[],char content[]){
	int i;
	for(i = 0; i < 8;i++)content[i]=regist[i];	
}

void writeRegister(char regist[],char content[]){
	int i;
	for(i = 0; i < 8;i++)regist[i]=content[i];
}