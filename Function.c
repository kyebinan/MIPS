#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryManagement.h"
#include "RegistryManagement.h"
#include "Utility.h"
#include "Function.h"

/*-----------------------------------------------------------------------------------*/
/*------We treat the case our R-instruction is of the format: << FUNCTION rd >>------*/
/*-----------------------------------------------------------------------------------*/
	

void MFLO(char rd[],char Tab[35][10]){
	char content[100],ch[100];
	int c,i;

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	writeRegister(Tab[atoi(rd)],Tab[32]);
	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c += 4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content);
	writeRegister(Tab[34],content);
}

void MFHI(char rd[],char Tab[35][10]){
	char content[100],ch[100];
	int c,i;

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	writeRegister(Tab[atoi(rd)],Tab[33]);
	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c += 4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content);
	writeRegister(Tab[34],content);
}

void JR(char rd[],char Tab[35][10]){
	writeRegister(Tab[34],Tab[atoi(rd)]);
}

/*-----------------------------------------------------------------------------------*/
/*-----We treat the case our R-instruction is of the format: << FUNCTION rs,rt >>----*/
/*-----------------------------------------------------------------------------------*/

void MULT(char rs[],char rt[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	char debut[100],fin[100];
	int a,b,c,i;
	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	b = hexaSignedToDecimal(content2);
	sprintf(ch, "%d", a*b);
	/*Convertion sur 4  octets*/
	decimalToBinarySigned(ch, 64);

	for(i = 0; i < 32; i++) debut[i] = ch[i];
	for(i = 0; i < 32; i++) fin[i] = ch[32+i];

	binaryToHexa(debut, content1);
	binaryToHexa(fin, content2);
	/*écriture*/
	writeRegister(Tab[33],content1);
	writeRegister(Tab[32],content2);
	

	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	loadRegister(Tab[34],content1);
	c = hexaToDecimal(content1);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content1);
	writeRegister(Tab[34],content1);
}

void DIV(char rs[],char rt[],char Tab[35][10]){
	char content1[100],content2[100],ch1[100],ch2[100];
	int a,b,c,i;
	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	b = hexaSignedToDecimal(content2);
	sprintf(ch1, "%d", a/b);
	sprintf(ch2, "%d", a%b);
	/*Convertion sur 4  octets*/
	decimalToBinarySigned(ch1, 32);
	decimalToBinarySigned(ch2, 32);
	binaryToHexa(ch1, content1);
	binaryToHexa(ch2, content2);
	/*écriture*/
	writeRegister(Tab[33],content2);
	writeRegister(Tab[32],content1);

	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch1[i]='\0';
	loadRegister(Tab[34],content1);
	c = hexaToDecimal(content1);
	c +=4;
	sprintf(ch1, "%d", c);
	decimalToBinarySigned(ch1,32);
	binaryToHexa(ch1, content1);
	writeRegister(Tab[34],content1);
}

/*-----------------------------------------------------------------------------------*/
/*We treat the case our R-instruction= <<FUNCTION rd,rs,rt>> or <<FUNCTION rd,rt,sa>>*/
/*-----------------------------------------------------------------------------------*/


/*----------------------------------First case----------------------------------*/
/*We treat the case our R-instruction is of the format: << FUNCTION rd,rs,rt >> */


void ADD(char rd[],char rs[],char rt[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	int a,b,c,i;
	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch[i]='\0';
	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	b = hexaSignedToDecimal(content2);
	sprintf(ch, "%d", a+b);
	/*Convertion sur 4  octets*/
	decimalToBinarySigned(ch, 32);
	binaryToHexa(ch, content1);
	/*écriture*/
	writeRegister(Tab[atoi(rd)],content1);

	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	loadRegister(Tab[34],content1);
	c = hexaToDecimal(content1);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content1);
	writeRegister(Tab[34],content1);

}

void SUB(char rd[],char rs[],char rt[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	int a,b,c,i;
	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch[i]='\0';
	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	b = hexaSignedToDecimal(content2);
	sprintf(ch, "%d", a-b);
	/*Convertion sur 4  octets*/
	decimalToBinarySigned(ch, 32);
	binaryToHexa(ch, content1);
	/*écriture*/
	writeRegister(Tab[atoi(rd)],content1);

	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	loadRegister(Tab[34],content1);
	c = hexaToDecimal(content1);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content1);
	writeRegister(Tab[34],content1);
}

void AND(char rd[],char rs[],char rt[],char Tab[35][10]){
	char content1[100],content2[100],ch1[100],ch2[100];
	int i,c;
	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch1[i]='\0';
	for(i=0;i<100;i++)ch2[i]='\0';
	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	hexaToBinary(content1,ch1);
	hexaToBinary(content2,ch2);
	
	for (i = 0; i < 32; i++) ch1[i] = (ch1[i]=='1' && ch2[i]=='1') ? '1' : '0' ;
	binaryToHexa(ch1, content1);
	/*écriture*/
	writeRegister(Tab[atoi(rd)],content1);

	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch1[i]='\0';
	loadRegister(Tab[34],content1);
	c = hexaToDecimal(content1);
	c +=4;
	sprintf(ch1, "%d", c);
	decimalToBinarySigned(ch1,32);
	binaryToHexa(ch1, content1);
	writeRegister(Tab[34],content1);
}

void OR(char rd[],char rs[],char rt[],char Tab[35][10]){
	char content1[100],content2[100],ch1[100],ch2[100];
	int i,c;
	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch1[i]='\0';
	for(i=0;i<100;i++)ch2[i]='\0';
	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	hexaToBinary(content1,ch1);
	hexaToBinary(content2,ch2);
	
	for (i = 0; i < 32; i++) ch1[i] = (ch1[i]=='1' || ch2[i]=='1') ? '1' : '0' ;
	binaryToHexa(ch1, content1);
	/*écriture*/
	writeRegister(Tab[atoi(rd)],content1);

	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch1[i]='\0';
	loadRegister(Tab[34],content1);
	c = hexaToDecimal(content1);
	c +=4;
	sprintf(ch1, "%d", c);
	decimalToBinarySigned(ch1,32);
	binaryToHexa(ch1, content1);
	writeRegister(Tab[34],content1);
}

void XOR(char rd[],char rs[],char rt[],char Tab[35][10]){
	char content1[100],content2[100],ch1[100],ch2[100];
	int i,c;
	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch1[i]='\0';
	for(i=0;i<100;i++)ch2[i]='\0';
	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	hexaToBinary(content1,ch1);
	hexaToBinary(content2,ch2);
	
	for (i = 0; i < 32; i++) ch1[i] = (ch1[i] != ch2[i]) ? '1' : '0' ;
	binaryToHexa(ch1, content1);
	/*écriture*/
	writeRegister(Tab[atoi(rd)],content1);

	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch1[i]='\0';
	loadRegister(Tab[34],content1);
	c = hexaToDecimal(content1);
	c +=4;
	sprintf(ch1, "%d", c);
	decimalToBinarySigned(ch1,32);
	binaryToHexa(ch1, content1);
	writeRegister(Tab[34],content1);
}

void SLT(char rd[],char rs[],char rt[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	char False[12] ="00000000"; 
	char True[12]  ="00000001"; 
	int a,b,c,i;
	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	for(i=0;i<100;i++)ch[i]='\0';
	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	b = hexaSignedToDecimal(content2);

	if (a < b) writeRegister(Tab[atoi(rd)],True);
	else writeRegister(Tab[atoi(rd)],False);

	for(i=0;i<100;i++)content1[i]='\0';
	for(i=0;i<100;i++)content2[i]='\0';
	loadRegister(Tab[34],content1);
	c = hexaToDecimal(content1);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content1);
	writeRegister(Tab[34],content1);
}

/*----------------------------------Second case----------------------------------*/
/*We treat the case our R-instruction is of the format:  << FUNCTION rd,rt,sa >> */

void ROTR(char rd[],char rt[],char sa[],char Tab[35][10]){
	char content[100],ch1[100],ch2[100];
	int a,c,i;
	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch1[i]='\0';}

	for(i=0;i<100;i++)
		{ch2[i]='\0';}

	loadRegister(Tab[atoi(rt)],content);
	/*Convertion en entier signed*/
	hexaToBinary(content,ch1);
	a = atoi(sa);
	if (a % 2 == 0)writeRegister(Tab[atoi(rd)],content);
	else{
		for(i = 0; i < 32; i++)ch2[i] = ch1[31-i];
		binaryToHexa(ch2, content);
		writeRegister(Tab[atoi(rd)],content);
	}

	for(i=0;i<100;i++)content[i]='\0';
	for(i=0;i<100;i++)ch1[i]='\0';
	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c +=4;
	sprintf(ch1, "%d", c);
	decimalToBinarySigned(ch1,32);
	binaryToHexa(ch1, content);
	writeRegister(Tab[34],content);
}

void SLL(char rd[],char rt[],char sa[],char Tab[35][10]){
	char content[100], ch[100];
	int a,c,i,j;

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[atoi(rt)],content);
	/*Convertion en entier signed*/
	hexaToBinary(content,ch);
	a = atoi(sa);
	for(i = a, j=0; i < 31; i++, j++)
		{ch[j]=ch[i];}
	for(i = 31 - a; i < 31; i++)
		{ch[i]='0';}
	binaryToHexa(ch, content);
	writeRegister(Tab[atoi(rd)],content);

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content);
	writeRegister(Tab[34],content);
}

void SRL(char rd[],char rt[],char sa[],char Tab[35][10]){
	char content[100], ch[100];
	int a,c,i,j;

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[atoi(rt)],content);
	/*Convertion en entier signed*/
	hexaToBinary(content,ch);
	a = atoi(sa);

	for(i = 31-a,j=31; i >= 0;i--,j--)
		{ch[j]=ch[i];}

	for(i = 0 ;i < a;i++)
		{ch[i]='0';}

	binaryToHexa(ch, content);
	writeRegister(Tab[atoi(rd)],content);

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content);
	writeRegister(Tab[34],content);
}


/*-----------------------------------------------------------------------------------*/
/*------We treat the case our I-instruction is of the format: << FUNCTION rd >>------*/
/*-----------------------------------------------------------------------------------*/
	

void ADDI(char rt[],char rs[],char immediat[],char Tab[35][10]){
	char content[100], ch[100];
	int a,b,c,i;
	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[atoi(rs)],content);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content);
	b = (strstr(immediat,"-")) ? -atoi(immediat) :atoi(immediat);
	sprintf(ch, "%d", a+b);
	/*Convertion sur 4  octets*/
	decimalToBinarySigned(ch, 32);
	binaryToHexa(ch, content);
	/*écriture*/
	writeRegister(Tab[atoi(rt)],content);

	for(i=0;i<100;i++)
		{content[i]='\0';}

	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content);
	writeRegister(Tab[34],content);
}

void LW(char rt[],char offset[],char base[],char Tab[35][10],char RAM[][4]){
	char content[100], ch[100];
	int adr,a,c,i;

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	a = (strstr(offset,"-")) ? -atoi(offset) :atoi(offset);
	adr = hexaToDecimal(Tab[atoi(base)])+a;
	loadWord(adr,RAM,content);
	writeRegister(Tab[atoi(rt)],content);

	for(i=0;i<100;i++)
		{content[i]='\0';}

	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content);
	writeRegister(Tab[34],content);
}

void SW(char rt[],char offset[],char base[],char Tab[35][10],char RAM[][4]){
	char content[100], ch[100];
	int adr,a,c,i;

	for(i=0;i<100;i++)
		{content[i]='\0';}
	
	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[atoi(rt)],content);
	a = (strstr(offset,"-")) ? -atoi(offset) :atoi(offset);
	adr = hexaToDecimal(Tab[atoi(base)])+a;
	storeWord(adr,RAM,content);

	for(i=0;i<100;i++)
		{content[i]='\0';}

	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content);
	writeRegister(Tab[34],content);
}

void LUI(char rt[],char immediat[],char Tab[35][10]){
	char content[100],ch[100];
	int i,c;

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	decimalToBinarySigned(immediat,16);
	loadRegister(Tab[atoi(rt)],content);
	/*Convertion en entier signed*/
	hexaToBinary(content,ch);
	
	for (i = 0; i < 16; i++) 
		{ch[i] = immediat[i] ;}

	binaryToHexa(ch, content);
	/*écriture*/
	writeRegister(Tab[atoi(rt)],content);

	for(i=0;i<100;i++)
		{content[i]='\0';}

	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[34],content);
	c = hexaToDecimal(content);
	c +=4;
	sprintf(ch, "%d", c);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content);
	writeRegister(Tab[34],content);
}

void BEQ(char rs[],char rt[],char offset[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	int a,b,c,i;

	for(i=0;i<100;i++)
		{content1[i]='\0';}
	for(i=0;i<100;i++)
		{content2[i]='\0';}
	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	b = hexaSignedToDecimal(content2);

	if (a == b) {
		for(i=0;i<100;i++)
			{content1[i]='\0';}

		for(i=0;i<100;i++)
			{content2[i]='\0';}
		decimalToBinarySigned(offset, 32);
		binaryToHexa(offset, content2);
		loadRegister(Tab[34],content1);
		c = hexaToDecimal(content1);
		c+=hexaToDecimal(content2);
		sprintf(ch, "%d", c);
		decimalToBinarySigned(ch,32);
		binaryToHexa(ch, content1);
		writeRegister(Tab[34],content1);
	}
	else {
		for(i=0;i<100;i++)
			{content1[i]='\0';}

		for(i=0;i<100;i++)
			{content2[i]='\0';}
		loadRegister(Tab[34],content1);
		c = hexaToDecimal(content1);
		c +=4;
		sprintf(ch, "%d", c);
		decimalToBinarySigned(ch,32);
		binaryToHexa(ch, content1);
		writeRegister(Tab[34],content1);
	}
}

void BNE(char rs[],char rt[],char offset[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	
	int a,b,c,i;
	for(i=0;i<100;i++)
		{content1[i]='\0';}
	for(i=0;i<100;i++)
		{content2[i]='\0';}
	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[atoi(rs)],content1);
	loadRegister(Tab[atoi(rt)],content2);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	b = hexaSignedToDecimal(content2);

	if (a != b) {
		decimalToBinarySigned(offset, 32);
		binaryToHexa(offset, content2);
		loadRegister(Tab[34],content1);
		c = hexaToDecimal(content1)+hexaToDecimal(content2);
		sprintf(ch, "%d", c);
		decimalToBinarySigned(ch,32);
		binaryToHexa(ch, content1);
		writeRegister(Tab[34],content1);
	}
	else {
		loadRegister(Tab[34],content1);
		c = hexaToDecimal(content1);
		c +=4;
		sprintf(ch, "%d", c);
		decimalToBinarySigned(ch,32);
		binaryToHexa(ch, content1);
		writeRegister(Tab[34],content1);
	}
}

void BGTZ(char rs[],char offset[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	int a,c,i;

	for(i=0;i<100;i++)
		{content1[i]='\0';}
	for(i=0;i<100;i++)
		{content2[i]='\0';}
	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[atoi(rs)],content1);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	
	if (a > 0) {
		decimalToBinarySigned(offset, 32);
		binaryToHexa(offset, content2);
		loadRegister(Tab[34],content1);
		c = hexaToDecimal(content1)+hexaToDecimal(content2);
		sprintf(ch, "%d", c);
		decimalToBinarySigned(ch,32);
		binaryToHexa(ch, content1);
		writeRegister(Tab[34],content1);
	}
	else {
		loadRegister(Tab[34],content1);
		c = hexaToDecimal(content1);
		c +=4;
		sprintf(ch, "%d", c);
		decimalToBinarySigned(ch,32);
		binaryToHexa(ch, content1);
		writeRegister(Tab[34],content1);
	}
}

void BLEZ(char rs[],char offset[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	
	int a,c,i;
	for(i=0;i<100;i++)
		{content1[i]='\0';}
	for(i=0;i<100;i++)
		{content2[i]='\0';}
	for(i=0;i<100;i++){ch[i]='\0';}

	loadRegister(Tab[atoi(rs)],content1);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	

	if (a <= 0) {
		decimalToBinarySigned(offset, 32);
		binaryToHexa(offset, content2);
		loadRegister(Tab[34],content1);
		c = hexaToDecimal(content1)+hexaToDecimal(content2);
		sprintf(ch, "%d", c);
		decimalToBinarySigned(ch,32);
		binaryToHexa(ch, content1);
		writeRegister(Tab[34],content1);
	}
	else {
		loadRegister(Tab[34],content1);
		c = hexaToDecimal(content1);
		c +=4;
		sprintf(ch, "%d", c);
		decimalToBinarySigned(ch,32);
		binaryToHexa(ch, content1);
		writeRegister(Tab[34],content1);
	}
}


/*-----------------------------------------------------------------------------------*/
/*---We treat the case our J-instruction is of the format: << FUNCTION immediat >>---*/
/*-----------------------------------------------------------------------------------*/
	

void Jump(char index[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	int a,i;

	for(i=0;i<100;i++)
		{content1[i]='\0';}
	for(i=0;i<100;i++)
		{content2[i]='\0';}
	for(i=0;i<100;i++)
		{ch[i]='\0';}

	//loadRegister(Tab[34],content1);
	decimalToBinarySigned(index, 32);
	//a = hexaSignedToDecimal(content1);
	binaryToHexa(index, content2);
	a = hexaToDecimal(content2);
	sprintf(ch, "%d", a);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content1);
	writeRegister(Tab[34],content1);
}

void JAL(char index[],char Tab[35][10]){
	char content1[100],content2[100],ch[100];
	
	int a,i;
	for(i=0;i<100;i++)
		{content1[i]='\0';}
	for(i=0;i<100;i++)
		{content2[i]='\0';}
	for(i=0;i<100;i++)
		{ch[i]='\0';}

	loadRegister(Tab[34],content1);
	/*Convertion en entier signed*/
	a = hexaSignedToDecimal(content1);
	a+=4;
	sprintf(ch, "%d", a);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content1);
	writeRegister(Tab[31],content1);

	decimalToBinarySigned(index, 32);
	binaryToHexa(index, content2);
	a = hexaToDecimal(content2);
	sprintf(ch, "%d", a);
	decimalToBinarySigned(ch,32);
	binaryToHexa(ch, content1);
	writeRegister(Tab[34],content1);
}





























