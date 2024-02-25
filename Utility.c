#include "Utility.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *HEXA[] = {"0000",
				"0001",
				"0010",
				"0011",
				"0100",
				"0101",
				"0110",
				"0111",
				"1000",
				"1001",
				"1010",
				"1011",
				"1100",
				"1101",
				"1110",
				"1111"};

char *MEMONIC[] = {"zero","at","v0","v1","a0","a1","a2","a3",
					"t0","t1","t2","t3","t4","t5","t6","t7",
					"s0","s1","s2","s3","s4","s5","s6","s7",
					"t8","t9","k0","k1","gp","sp","fp","ra"};

char *regList[] = {"0","1","2","3","4","5","6","7",
					"8","9","10","11","12","13","14","15",
					"16","17","18","19","20","21","22","23",
					"24","25","26","27","28","29","30","31"};

void checkRegisters(char regist[]){
	int i,j, val = 0;
	for(i = 0; regist[i]!='\0'; i++){
		if (regist[i] == ' ' || regist[i] == '\n')regist[i] = '\0';
	}

	for(i = 0;  val == 0 && i<32 ; i++){
		if (strcmp(regist, regList[i])== 0) val = 1;
		else if (strcmp(regist, MEMONIC[i])== 0){
			for(j = 0; j < 5; j++)regist[j]= '\0';
			for(j = 0; regList[i][j] != 0; j++) regist[j]= regList[i][j];
			val = 1;
		}
	}
	if ( val == 0 && i == 31){
		perror("Problem register is wrong");
		exit(1);
	}
}

void decimalToBinary(char ch[], int nbit){
	int nb = atoi(ch);
	int i,j;
	for(j = nbit-1, i = nb; j >= 0; j--, i/=2){
		if(i%2 == 0)ch[j]= '0';
		else ch[j]= '1';
	}
}

void decimalToBinarySigned(char ch[], int nbit){
	if (ch[0] == '-'){
		int i;
		ch[0] = ' ';
		decimalToBinary(ch, nbit);
		/*complément a 2*/
		for (i = 0; i < nbit; i++) ch[i] = (ch[i]=='1') ? '0' : '1' ;

		if (ch[nbit-1] == '0')ch[nbit-1] = '1';
		else for (i = nbit-1; ch[i]!='0';i--)ch[i]='0';
		ch[i] ='1';
	}
	else decimalToBinary(ch, nbit);
}

void binaryToHexa(char bin[], char hexa[]){
	char ch[6];
	int i,j =0;
	/*We initialize all the characters of the array to '\0' */
	for (i = 0; i < 6; i++)ch[i] = '\0';
	/*We split each byte in two for the conversion */
	for (i = 0; i < 8; i++){
		for(j = 0; j < 4;  j++){
			ch[j] = bin[i*4 + j];
		}
		if      (strcmp(ch, HEXA[0])==0)  hexa[i] = '0';
		else if (strcmp(ch, HEXA[1])==0)  hexa[i] = '1';
		else if (strcmp(ch, HEXA[2])==0)  hexa[i] = '2';
		else if (strcmp(ch, HEXA[3])==0)  hexa[i] = '3';
		else if (strcmp(ch, HEXA[4])==0)  hexa[i] = '4';
		else if (strcmp(ch, HEXA[5])==0)  hexa[i] = '5';
		else if (strcmp(ch, HEXA[6])==0)  hexa[i] = '6';
		else if (strcmp(ch, HEXA[7])==0)  hexa[i] = '7';
		else if (strcmp(ch, HEXA[8])==0)  hexa[i] = '8';
		else if (strcmp(ch, HEXA[9])==0)  hexa[i] = '9';
		else if (strcmp(ch, HEXA[10])==0) hexa[i] = 'A';
		else if (strcmp(ch, HEXA[11])==0) hexa[i] = 'B';
		else if (strcmp(ch, HEXA[12])==0) hexa[i] = 'C';
		else if (strcmp(ch, HEXA[13])==0) hexa[i] = 'D';
		else if (strcmp(ch, HEXA[14])==0) hexa[i] = 'E';
		else if (strcmp(ch, HEXA[15])==0) hexa[i] = 'F';
	}
}

int hexaToDecimal(char hexa[]){
	int i, n = 0;
	for(i = 7; i > 0; i--){
		switch (hexa[7-i]){
			case 'F': n = (n + 15)*16;break;
			case 'E': n = (n + 14)*16;break;
			case 'D': n = (n + 13)*16;break;
			case 'C': n = (n + 12)*16;break;
			case 'B': n = (n + 11)*16;break;
			case 'A': n = (n + 10)*16;break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':n = (n + (hexa[7-i] - '0'))*16;break;
			default: return -1;
		}
	}
	switch (hexa[7-i]){
		case 'F': n += 15;break;
		case 'E': n += 14;break;
		case 'D': n += 13;break;
		case 'C': n += 12;break;
		case 'B': n += 11;break;
		case 'A': n += 10;break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':n = (n + (hexa[7-i] - '0'));break;
		default: return -1;
	}
	return n;
}

void hexaToBinary(char hexa[],char bin[]){
	int i,j,k;

	for(i=0; i<8; i++){
		if      (hexa[i] == '0') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[0][k];
		else if (hexa[i] == '1') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[1][k];
		else if (hexa[i] == '2') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[2][k];
		else if (hexa[i] == '3') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[3][k];
		else if (hexa[i] == '4') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[4][k];
		else if (hexa[i] == '5') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[5][k];
		else if (hexa[i] == '6') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[6][k];
		else if (hexa[i] == '7') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[7][k];
		else if (hexa[i] == '8') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[8][k];
		else if (hexa[i] == '9') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[9][k];
		else if (hexa[i] == 'A') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[10][k];
		else if (hexa[i] == 'B') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[11][k];
		else if (hexa[i] == 'C') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[12][k];
		else if (hexa[i] == 'D') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[13][k];
		else if (hexa[i] == 'E') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[14][k];
		else if (hexa[i] == 'F') for(j = i*4,k = 0; j<(i+1)*4 ; j++,k++) bin[j] = HEXA[15][k];
	}
}

int hexaSignedToDecimal(char hexa[]){
	int i, N=0;
	char bin[100];
	hexaToBinary(hexa, bin);
	if (bin[0]=='0'){
		for(i = 31; i > 0; i--) N = (N + (bin[31-i] - '0'))*2;
		N = (N + (bin[31-i] - '0'));
		return N;
	}

	else{
		/*complément a 2*/
		for (i = 0; i < 32; i++) bin[i] = (bin[i]=='1') ? '0' : '1' ;

		if (bin[31] == '0')bin[31] = '1';
		else for (i = 31; bin[i]!='0';i--)bin[i]='0';
		bin[i] ='1';

		for(i = 31; i > 0; i--) N = (N + (bin[31-i] - '0'))*2;
		N = (N + (bin[31-i] - '0'));
		return -N;

	}
}
















