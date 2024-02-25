#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HexaConverte.h"
#include "MemoryManagement.h"
#include "RegistryManagement.h"
#include "Utility.h"

char *R_LIST[] = {"ADD","SUB","MULT","DIV","AND","OR","XOR",
				"ROTR","SLL","SRL","SLT","MFHI","MFLO","JR",};
char *RCODE[] = {"100000","100010","011000","011010","100100","100101","100110",
				"000010","000000","000010","101010","010000","010010","001000"};

char *I_LIST[] = {"ADDI","LW","SW","LUI","BEQ","BNE","BGTZ","BLEZ"};
char *ICODE[] = {"001000","100011","101011","001111","000100","000101","000111","000110"};

char *J_LIST[] =  {"J", "JAL"};
char *JCODE[] = {"000010","000011"};

void instructionExtraction(char *fileLine, char *instr){
	/*the function takes as argument the string fileLine containing a line code 
	from the text file and extracts the instruction in the string instr*/

	if (*fileLine == '#'){
		/*We have a comment, we ignore the whole line*/
		*instr = '#';
	}

	else if (*fileLine == '\0'){
		/*We have an empty line, we ignore the whole line*/
		*instr = '#';
	}
	else if (*fileLine == '\n'){
		/*We have an empty line, we ignore the whole line*/
		*instr = '#';
	}
	else if (*fileLine == '\t'){
		/*We have an empty line, we ignore the whole line*/
		*instr = '#';
	}
	else if (*fileLine == '\v'){
		/*We have an empty line, we ignore the whole line*/
		*instr = '#';
	}
	else if (*fileLine == '\f'){
		/*We have an empty line, we ignore the whole line*/
		*instr = '#';
	}
	else if (*fileLine == '\r'){
		/*We have an empty line, we ignore the whole line*/
		*instr = '#';
	}
	else {
		while(*fileLine != '\0' && *fileLine != '#' ){
			/*We copy the fileLine in instr without the comment if it exists*/
			*instr = *fileLine;
			fileLine++; instr++;
		}
	}
}

int instructionType(char *instr){
	/*the function returns the type of instruction entered as argument*/

	char function[12];
	int i;
	enum TypeInstruction type;

	for(i = 0; i < 12; i++)function[i]='\0';
	/*We extract the function of the instr string to find the type of the instruction*/
	for(i = 0; *instr != ' ' && *instr != '\0' && *instr != '\n';instr++,i++)
		function[i]= *instr; 

	/*We look for the type of the instruction*/
	if (strcmp(function, "NOP") == 0)return type = NOP;

	else{
		for(i = 0; i < 14; i++){
			if (strcmp(function, R_LIST[i]) == 0)return type = R;
		}
		for(i = 0; i < 8; i++){
			if (strcmp(function, I_LIST[i]) == 0)return type = I;
		}
		for(i = 0; i < 2; i++){
			if (strcmp(function, J_LIST[i]) == 0)return type = J;
		}
		/*If we arrive here it is because the instruction entered is not listed*/
		return ERROR;
	}
}

void giveR_code(char function[]){
	/*the function give the opcode of the R-instruction*/
	int i;
	if (strcmp(function, R_LIST[0])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[0][i]; 
	else if (strcmp(function, R_LIST[1])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[1][i];
	else if (strcmp(function, R_LIST[2])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[2][i];
	else if (strcmp(function, R_LIST[3])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[3][i];
	else if (strcmp(function, R_LIST[4])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[4][i];
	else if (strcmp(function, R_LIST[5])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[5][i];
	else if (strcmp(function, R_LIST[6])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[6][i];
	else if (strcmp(function, R_LIST[7])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[7][i];
	else if (strcmp(function, R_LIST[8])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[8][i];
	else if (strcmp(function, R_LIST[9])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[9][i];
	else if (strcmp(function, R_LIST[10])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[10][i];
	else if (strcmp(function, R_LIST[11])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[11][i];
	else if (strcmp(function, R_LIST[12])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[12][i];
	else if (strcmp(function, R_LIST[13])==0) 
		for(i = 0; i < 6; i++) function[i] = RCODE[13][i];
}

void R_instructionToHexa(char *instr, char hexa[]){
	/*the function convert a R-instruction in Hexadecimal*/

	char function[N];
	int i, nbArguments = 0, nbRegisters = 0;
	char *instrCp = instr;
	enum value egal = True;
	/*We initialize all characters to null*/
	for (i = 0;i < N;i++)function[i] = '\0';

	/*We cut the instruction to collect the differents fields
	We first extract the function of the instr string */
	for(i = 0; *instr != ' ';instr++,i++)function[i]= *instr;
	for(;*instr != '\0';instr++){
		if (*instr == '$') nbRegisters++;
		if (*instr == ',') nbArguments++;
	}
	nbArguments++;

	/*-----------------------------------------------------------------------------------*/
	/*------We treat the case our R-instruction is of the format: << FUNCTION rd >>------*/
	/*-----------------------------------------------------------------------------------*/
	
	if (nbArguments == 1){
		/*We initialize the string that will contain rd*/
		char rd[N]; 
		/*We initialize all characters to null*/
		for(i = 0;i<N;i++)rd[i]='\0';

		egal = False;
		/*instrCp is a copy of the initial address of the first element of the string*/
		instr = instrCp;
		for(i = 0;*instr != '\0';instr++){
			if (egal == True) rd[i++] = *instr;
			if (*instr == '$') egal = True;
		}
		/*We initialize the string of bits which represents the instruction in binary*/
		char FourOctet[N];
		/*We initialize all characters to null*/
		for(i = 0;i<N;i++)FourOctet[i]='\0';

		checkRegisters(rd);
		for(i = 0;i<6;i++)FourOctet[i]='0';
		decimalToBinary(rd,5);
		char zero[] = "0000000000";

		/*-----------------------R_LIST[13] is the function JR--------------------------*/
		if (strcmp(function,R_LIST[13])==0){
			char hint[] = "00000";
			giveR_code(function);
			/*We concanete the strings*/
			strcat(FourOctet,rd);
			strcat(FourOctet,zero);
			strcat(FourOctet,hint);
			strcat(FourOctet,function);
			binaryToHexa(FourOctet,hexa);
			/*printf("==>> %s\n", FourOctet);/*i will delete after */
			/*printf("==>> %s\n", hexa);/*i will delete after */
		}

		/*-----------------the case where function is MFHI or MFLO----------------------*/
		else {
			char zero1[] = "00000";
			giveR_code(function);
			/*We concanete the strings*/
			strcat(FourOctet,zero);
			strcat(FourOctet,rd);
			strcat(FourOctet,zero1);
			strcat(FourOctet,function);
			binaryToHexa(FourOctet,hexa);
			/*printf("==>> %s\n", FourOctet);/*i will delete after */
			/*printf("==>> %s\n", hexa);/*i will delete after */
		}
	}	

	/*-----------------------------------------------------------------------------------*/
	/*-----We treat the case our R-instruction is of the format: << FUNCTION rs,rt >>----*/
	/*-----------------------------------------------------------------------------------*/
 	
	else if (nbArguments == 2){
		/*We initialize the strings that will contain rs and rt*/
		char rs[N], rt[N];
		/*We initialize all characters to null*/
		for(i = 0;i<N;i++)rs[i]='\0';
		for(i = 0;i<N;i++)rt[i]='\0';
		
		egal = False;
		int cmpt = 0, j;
		/*instrCp is a copy of the initial address of the first element of the string*/
		instr = instrCp;
		
		for(i = 0, j = 0;*instr != '\0';instr++){
			if (*instr == ',')egal = False;
			if (egal == True && cmpt == 1) rs[i++] = *instr;
			if (egal == True && cmpt == 2) rt[j++] = *instr;
			if (*instr == '$') {
				egal = True;
				cmpt++;
			}
		}

		checkRegisters(rt);
		checkRegisters(rs);
		
		decimalToBinary(rs,5);
		decimalToBinary(rt,5);

		/*We initialize the string of bits which represents the instruction in binary*/
		char FourOctet[33];
		/*We initialize all characters to null*/
		for(i = 0;i<33;i++)FourOctet[i]='\0';

		/*We fill the string with the 6 zeros of the spcial box*/
		for(i = 0;i<6;i++)FourOctet[i]='0';
		char zero[] = "0000000000";
		giveR_code(function);

		/*We concanete the strings*/
		strcat(FourOctet,rs);
		strcat(FourOctet,rt);
		strcat(FourOctet,zero);
		strcat(FourOctet,function);
		binaryToHexa(FourOctet,hexa);
		/*printf("==>> %s\n",FourOctet );/*i will delete after */
		/*printf("==>> %s\n",hexa );/*i will delete after */
	} 

	/*-----------------------------------------------------------------------------------*/
	/*We treat the case our R-instruction= <<FUNCTION rd,rs,rt>> or <<FUNCTION rd,rt,sa>>*/
	/*-----------------------------------------------------------------------------------*/

	else if (nbArguments == 3){

		/*----------------------------------First case----------------------------------*/
		/*We treat the case our R-instruction is of the format: << FUNCTION rd,rs,rt >> */

		if (nbRegisters == 3){
			/*We initialize the strings that will contain rd,rs and rt*/
			char rd[15], rs[15], rt[15];
			/*We initialize all characters to null*/
			for(i = 0;i<15;i++)rd[i]='\0';
			for(i = 0;i<15;i++)rs[i]='\0';
			for(i = 0;i<15;i++)rt[i]='\0';
			
			egal = False;
			int cmpt = 0, j, k;
			/*instrCp is a copy of the initial address of the first element of the string*/
			instr = instrCp;
			
			for(i = 0, j = 0, k = 0;*instr != '\0';instr++){
				if (*instr == ',')egal = False;
				if (egal == True && cmpt == 1) rd[i++] = *instr;
				if (egal == True && cmpt == 2) rs[j++] = *instr;
				if (egal == True && cmpt == 3) rt[k++] = *instr;
				if (*instr == '$') {
					egal = True;
					cmpt++;
				}
			}
			
			checkRegisters(rd);
			checkRegisters(rt);
			checkRegisters(rs);
			
			decimalToBinary(rd,5);
			decimalToBinary(rs,5);
			decimalToBinary(rt,5);

			/*We initialize the string of bits which represents the instruction in binary*/
			char FourOctet[33];
			/*We initialize all characters to null*/
			for(i = 0;i<33;i++)FourOctet[i]='\0';

			/*We fill the string with the 6 zeros of the spcial box*/
			for(i = 0;i<6;i++)FourOctet[i]='0';
			char zero[] = "00000";
			giveR_code(function);

			/*We concanete the strings*/
			strcat(FourOctet,rs);
			strcat(FourOctet,rt);
			strcat(FourOctet,rd);
			strcat(FourOctet,zero);
			strcat(FourOctet,function);
			binaryToHexa(FourOctet,hexa);
			/*printf("==>> %s\n",FourOctet );/*i will delete after */
			/*printf("==>> %s\n",hexa );/*i will delete after */
		}

		/*----------------------------------Second case----------------------------------*/
		/*We treat the case our R-instruction is of the format:  << FUNCTION rd,rt,sa >> */

		else if (nbRegisters == 2){
			/*We initialize the strings that will contain rd,rs and rt*/
			char rd[15], rt[15], sa[15];
			/*We initialize all characters to null*/
			for(i = 0;i<15;i++)rd[i]='\0';
			for(i = 0;i<15;i++)rt[i]='\0';
			for(i = 0;i<15;i++)sa[i]='\0';
			
			egal = False;
			int cmpt1 = 0, cmpt2 = 0, j, k;
			/*instrCp is a copy of the initial address of the first element of the string*/
			instr = instrCp;
			
			for(i = 0, j = 0, k = 0;*instr != '\0';instr++){
				if (cmpt2 == 2) sa[k++] = *instr;
				if (*instr == ','){egal = False; cmpt2++;}
				if (egal == True && cmpt1 == 1) rd[i++] = *instr;
				if (egal == True && cmpt1 == 2) rt[j++] = *instr;
				if (*instr == '$') {egal = True; cmpt1++;}
			}
			
			checkRegisters(rd);
			checkRegisters(rt);
			
			decimalToBinary(rd,5);
			decimalToBinary(rt,5);
			decimalToBinary(sa,5);

			/*We initialize the string of bits which represents the instruction in binary*/
			char FourOctet[33];
			/*We initialize all characters to null*/
			for(i = 0;i<33;i++)FourOctet[i]='\0';
			/*We fill the string with the 6 zeros of the spcial box*/
			for(i = 0;i<6;i++)FourOctet[i]='0';
			
			/*R_LIST[8] is the function SLL*/
			if (strcmp(function,R_LIST[8])==0){
				char zero[] = "00000";
				giveR_code(function);
				/*We concanete the strings*/
				strcat(FourOctet,zero);
				strcat(FourOctet,rt);
				strcat(FourOctet,rd);
				strcat(FourOctet,sa);
				strcat(FourOctet,function);
				binaryToHexa(FourOctet,hexa);
				/*printf("==>> %s\n",FourOctet );/*i will delete after */
				/*printf("==>> %s\n",hexa );/*i will delete after */
			}
			else{
				char r[15]; 
				for(i = 0;i<15;i++)r[i]='\0';
				/*R_LIST[7] is the function ROTR*/
				if (strcmp(function,R_LIST[7])==0)r[0]='1';
				/*R_LIST[9] is the function SRL*/
				else if (strcmp(function,R_LIST[9])==0)r[0]='0';
				char zero[] = "0000";
				giveR_code(function);
				/*We concanete the strings*/
				strcat(FourOctet,zero);
				strcat(FourOctet,r);
				strcat(FourOctet,rt);
				strcat(FourOctet,rd);
				strcat(FourOctet,sa);
				strcat(FourOctet,function);
				binaryToHexa(FourOctet,hexa);
				/*printf("==>> %s\n",FourOctet );/*i will delete after */
				/*printf("==>> %s\n",hexa );/*i will delete after */
			}
		}
	}
}

void giveI_code(char function[]){

	/*the function give the opcode of the I-instruction*/

	int i;
	if (strcmp(function, I_LIST[0])==0) 
		for(i = 0; i < 6; i++) function[i] = ICODE[0][i]; 
	else if (strcmp(function, I_LIST[1])==0) 
		for(i = 0; i < 6; i++) function[i] = ICODE[1][i];
	else if (strcmp(function, I_LIST[2])==0) 
		for(i = 0; i < 6; i++) function[i] = ICODE[2][i];
	else if (strcmp(function, I_LIST[3])==0) 
		for(i = 0; i < 6; i++) function[i] = ICODE[3][i];
	else if (strcmp(function, I_LIST[4])==0) 
		for(i = 0; i < 6; i++) function[i] = ICODE[4][i];
	else if (strcmp(function, I_LIST[5])==0) 
		for(i = 0; i < 6; i++) function[i] = ICODE[5][i];
	else if (strcmp(function, I_LIST[6])==0) 
		for(i = 0; i < 6; i++) function[i] = ICODE[6][i];
	else if (strcmp(function, I_LIST[7])==0) 
		for(i = 0; i < 6; i++) function[i] = ICODE[7][i];
}

void I_instructionToHexa(char *instr, char hexa[]){

	/*the function convert a I-instruction in Hexadecimal*/

	char function[7];
	int i, nbArguments = 0, nbRegisters = 0;
	char *instrCp = instr;
	enum value egal = True, egal1 = True, egal2 = True;

	/*We initialize all characters to null*/
	for (i = 0;i < 7;i++)function[i] = '\0';
	for(i = 0; *instr != ' ';instr++,i++)function[i]= *instr;

	if (strcmp(function, I_LIST[1])==0 || strcmp(function, I_LIST[2])==0){
		egal = False;
		egal1 = False;
		egal2 = False;
		int cmpt1 = 0, cmpt2 = 0, j, k;
		char rt[N],offset[N],base[N];

		for (i = 0;i < N;i++)rt[i] = '\0';
		for (i = 0;i < N;i++)offset[i] = '\0';
		for (i = 0;i < N;i++)base[i] = '\0';

		/*instrCp is a copy of the initial address of the first element of the string*/
		instr = instrCp;
			
		for(i = 0, j = 0, k = 0;*instr != '\0';instr++){
			if (*instr == ')') egal2 = False;
			if (egal2 == True)base[k++] = *instr;
			if (*instr == '(' && *(instr+1) == '$'){egal1 = False;egal2 =True;instr++;}
			if (egal1 == True) offset[j++] =*instr;
			if (*instr == ','){egal = False; egal1 = True;}
			if (egal == True) rt[i++] =*instr;
			if (*instr == '$' && *(instr-1)!='(') {egal = True; }
		}
		
		checkRegisters(rt);
		
		decimalToBinary(rt,5);
		decimalToBinarySigned(offset,16);
		decimalToBinary(base,5);

		/*We initialize the string of bits which represents the instruction in binary*/
		char FourOctet[N];
		/*We initialize all characters to null*/
		for(i = 0;i<N;i++)FourOctet[i]='\0';

		/*We fill the string with the 6 zeros of the spcial box*/
		giveI_code(function);
		for(i = 0;i<6;i++)FourOctet[i]=function[i];

		/*We concanete the strings*/
		strcat(FourOctet,base);
		strcat(FourOctet,rt);
		strcat(FourOctet,offset);
		binaryToHexa(FourOctet,hexa);
		/*printf("==>> %s\n",FourOctet );/*i will delete after */
		/*printf("==>> %s\n",hexa );/*i will delete after */
	}

	else {
		/*We cut the instruction to collect the differents fields
		We first extract the function of the instr string */

		for(;*instr != '\n';instr++){
			if (*instr == '$') nbRegisters++;
			if (*instr == ',') nbArguments++;
		}
		nbArguments++;


		if (nbArguments == 3){
			char rs[N], rt[N], offset[N];
			/*We initialize all characters to null*/
			for(i = 0;i<N;i++)rs[i]='\0';
			for(i = 0;i<N;i++)rt[i]='\0';
			for(i = 0;i<N;i++)offset[i]='\0';
			
			egal = False;
			int cmpt1 = 0, cmpt2 = 0, j, k;
			/*instrCp is a copy of the initial address of the first element of the string*/
			instr = instrCp;
			
			if (strcmp(function, I_LIST[0])==0){
				for(i = 0, j = 0, k = 0;*instr != '\0';instr++){
					if (cmpt2 == 2) offset[k++] = *instr;
					if (*instr == ','){egal = False; cmpt2++;}
					if (egal == True && cmpt1 == 1) rt[i++] = *instr;
					if (egal == True && cmpt1 == 2) rs[j++] = *instr;
					if (*instr == '$') {egal = True; cmpt1++;}
				}
			}

			else{
				for(i = 0, j = 0, k = 0;*instr != '\0';instr++){
					if (cmpt2 == 2) offset[k++] = *instr;
					if (*instr == ','){egal = False; cmpt2++;}
					if (egal == True && cmpt1 == 1) rs[i++] = *instr;
					if (egal == True && cmpt1 == 2) rt[j++] = *instr;
					if (*instr == '$') {egal = True; cmpt1++;}
				}
			}
			
			checkRegisters(rt);
			checkRegisters(rs);
			
			decimalToBinary(rt,5);
			decimalToBinarySigned(offset,16);
			decimalToBinary(rs,5);
			/*We initialize the string of bits which represents the instruction in binary*/
			char FourOctet[N];
			/*We initialize all characters to null*/
			for(i = 0;i<N;i++)FourOctet[i]='\0';

			/*We fill the string with the 6 zeros of the spcial box*/
			giveI_code(function);
			for(i = 0;i<6;i++)FourOctet[i]=function[i];

			/*We concanete the strings*/
			strcat(FourOctet,rs);
			strcat(FourOctet,rt);
			strcat(FourOctet,offset);
			binaryToHexa(FourOctet,hexa);
			/*printf("==>> %s\n",FourOctet );/*i will delete after */
			/*printf("==>> %s\n",hexa );/*i will delete after */

		}

		else if (nbArguments == 2){
			/*We initialize the strings that will contain rs and rt*/
			char rs[N], offset[N];
			/*We initialize all characters to null*/
			for(i = 0;i<N;i++)rs[i]='\0';
			for(i = 0;i<N;i++)offset[i]='\0';
			
			egal = False;
			egal1 = False;
			int cmpt = 0, j;
			/*instrCp is a copy of the initial address of the first element of the string*/
			instr = instrCp;
			
			for(i = 0, j = 0;*instr != '\0';instr++){
				if (egal1 == True ) offset[i++] = *instr;
				if (*instr == ',') {egal = False; egal1 =True;}
				if (egal == True ) rs[j++] = *instr;
				if (*instr == '$') egal = True;
			}
			
			checkRegisters(rs);
			
			decimalToBinarySigned(offset,16);
			decimalToBinary(rs,5);

			/*We initialize the string of bits which represents the instruction in binary*/
			char FourOctet[N];
			/*We initialize all characters to null*/
			for(i = 0;i<N;i++)FourOctet[i]='\0';

			/*We fill the string with the 6 zeros of the spcial box*/
			char zero[] = "00000";

			if (strcmp(function, I_LIST[3])==0){
				giveI_code(function);
				for(i = 0;i<6;i++)FourOctet[i]=function[i];
				/*We concanete the strings*/
				strcat(FourOctet,zero);
				strcat(FourOctet,rs);
				strcat(FourOctet,offset);
				binaryToHexa(FourOctet,hexa);
			}

			else{
				giveI_code(function);
				for(i = 0;i<6;i++)FourOctet[i]=function[i];
				/*We concanete the strings*/
				strcat(FourOctet,rs);
				strcat(FourOctet,zero);
				strcat(FourOctet,offset);
				binaryToHexa(FourOctet,hexa);
			}
			/*printf("==>> %s\n",FourOctet );/*i will delete after */
			/*printf("==>> %s\n",hexa );/*i will delete after */
		}
	}
}

void giveJ_code(char function[]){

	/*the function give the opcode of the J-instruction*/

	int i;
	if (strcmp(function, J_LIST[0])==0) 
		for(i = 0; i < 6; i++) function[i] = JCODE[0][i]; 
	else if (strcmp(function, J_LIST[1])==0) 
		for(i = 0; i < 6; i++) function[i] = JCODE[1][i];
}

void J_instructionToHexa(char *instr, char hexa[]){

	/*the function convert a I-instruction in Hexadecimal*/

	char function[7];
	int i;
	char *instrCp = instr;
	enum value egal = True;

	/*We initialize all characters to null*/
	for (i = 0;i < 7;i++)function[i] = '\0';
	for(i = 0; *instr != ' ';instr++,i++)function[i]= *instr;
	/*We initialize the string that will contain rd*/
	char target[30]; 
	/*We initialize all characters to null*/
	for(i = 0;i<30;i++)target[i]='\0';

	egal = False;
	/*instrCp is a copy of the initial address of the first element of the string*/
	instr = instrCp;
	for(i = 0;*instr != '\0';instr++){
		if (egal == True) target[i++] = *instr;
		if (*instr == ' ') egal = True;
	}
	
	decimalToBinary(target,26);
	/*We initialize the string of bits which represents the instruction in binary*/
	char FourOctet[N];
	/*We initialize all characters to null*/
	for(i = 0;i<N;i++)FourOctet[i]='\0';
	/*We fill the string with the 6 zeros of the spcial box*/
	giveJ_code(function);
	for(i = 0;i<6;i++)FourOctet[i]=function[i];
	/*We concanete the strings*/
	strcat(FourOctet,target);
	binaryToHexa(FourOctet,hexa);
	/*printf("==>> %s\n",FourOctet );/*i will delete after */
	/*printf("==>> %s\n",hexa );/*i will delete after */
}

void instructionToHexa(char *instr, char hexa[]){

	/*the function convert an instruction in Hexadecimal*/
	
	if (instructionType(instr)== R){
		R_instructionToHexa(instr, hexa);
	}
	else if (instructionType(instr)== I){
		I_instructionToHexa(instr, hexa);
	}
	else if (instructionType(instr)== J){
		J_instructionToHexa(instr, hexa);
	}
	else if (instructionType(instr)== NOP){
		int i;
		for(i = 0; i < 8; i++)hexa[i]='0';
	}
	else{
		printf("ERROR\n");
	}
}

void writeHexaFile(char *source,char *destination){

	/*the function write file text contaninig instruction in Hexadecimal*/

	FILE *scriptfile, *hexafile;
	scriptfile = fopen(source,"r");
	hexafile = fopen(destination,"w");

	if (scriptfile == NULL) {
		perror("Problem opening the source file ");
		exit(1);
	}
	if (hexafile == NULL) {
		perror("Problem opening the destination file ");
		exit(1);
	}

	char scriptLine[N];
	char instr[N];
	char hexa[N];
	int i;
	for(i = 0; i < N; i++) scriptLine[i] = '\0';
	for(i = 0; i < N; i++) instr[i] = '\0';
	for(i = 0; i < N; i++) hexa[i] = '\0';

	while(!feof(scriptfile)){
		fgets(scriptLine, N, scriptfile);
		instructionExtraction(scriptLine,instr);
		
		if (strcmp(instr, "#")==0) {
			for(i = 0; i < N; i++) instr[i] = '\0';
			for(i = 0; i < N; i++) hexa[i] = '\0';	
			//printf("*%s*\n",instr );
		}
		else{
			instructionToHexa(instr,hexa);
			fprintf(hexafile, "%s\n",hexa);
			for(i = 0; i < N; i++) instr[i] = '\0';
			for(i = 0; i < N; i++) hexa[i] = '\0';	
		}
	}
	fclose(scriptfile);
	fclose(hexafile);
}
/*
int main(int argc, char *argv[]){
	writeHexaFile(argv[1],argv[2]);

	int i;
	char reg1[10] = "000000BA";
	char reg2[10] = "00000000";
	char content[10] = "10";
	char content1[10] = "00000000";
	char content2[10] = "00000000";
	char RAM[1000][4];

	for(i = 0; i < 2; i++)RAM[hexaToDecimal("000000AA")][i] = 'B';
	for(i = 0; i < 2; i++)RAM[hexaToDecimal("000000AB")][i] = 'A';
	for(i = 0; i < 2; i++)RAM[hexaToDecimal("000000AC")][i] = 'C';
	for(i = 0; i < 2; i++)RAM[hexaToDecimal("000000AD")][i] = 'D';

	storeByte(hexaToDecimal("000000AF"),RAM,content);
	loadByte(hexaToDecimal("000000AF"),RAM,content);
	printf("%s\n",RAM[hexaToDecimal("000000AF")]);
	printf("%s\n",content);
	loadByte(hexaToDecimal("000000AB"),RAM,content);
	printf("%s\n",content);
	loadWord(hexaToDecimal("000000AA"),RAM,content1);
	printf("%s\n",content1);
	storeWord(hexaToDecimal("000000BA"),RAM,content1);
	loadWord(hexaToDecimal("000000BA"),RAM,content2);

	printf("==>%s\n",content1);
	loadRegister(reg1,content);
	writeRegister(reg1,content);
	printf("==>%s\n",content);
	return 0;
}*/