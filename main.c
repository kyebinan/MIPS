#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryManagement.h"
#include "RegistryManagement.h"
#include "HexaConverte.h"
#include "Utility.h"
#include "main.h"
#include "Function.h"


void R_instructionExecute(char *instr,char Tab[35][10]){
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
		checkRegisters(rd);

		if (strcmp(function,"MFLO")==0)MFLO(rd, Tab);
		else if(strcmp(function,"MFHI")==0)MFHI(rd, Tab);
		else if(strcmp(function,"JR")==0)JR(rd, Tab);	
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
		
		if (strcmp(function,"MULT")==0)MULT(rs, rt, Tab);
		else if(strcmp(function,"DIV")==0)DIV(rs, rt, Tab);	
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

			if (strcmp(function,"ADD")==0)ADD(rd, rs, rt, Tab);
			else if(strcmp(function,"SUB")==0)SUB(rd, rs, rt, Tab);	
			else if(strcmp(function,"AND")==0)AND(rd, rs, rt, Tab);	
			else if(strcmp(function,"OR")==0)OR(rd, rs, rt, Tab);	
			else if(strcmp(function,"XOR")==0)XOR(rd, rs, rt, Tab);	
			else if(strcmp(function,"SLT")==0)SLT(rd, rs, rt, Tab);	
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
			
			if (strcmp(function,"ROTR")==0)ROTR(rd ,rt , sa, Tab);
			else if(strcmp(function,"SLL")==0)SLL(rd ,rt , sa, Tab);	
			else if(strcmp(function,"SRL")==0)SRL(rd ,rt , sa, Tab);	
		}
	}
}

void I_instructionExecute(char *instr,char Tab[35][10],char RAM[][4]){

	/*the function convert a I-instruction in Hexadecimal*/

	char function[7];
	int i, nbArguments = 0, nbRegisters = 0;
	char *instrCp = instr;
	enum value egal = True, egal1 = True, egal2 = True;

	/*We initialize all characters to null*/
	for (i = 0;i < 7;i++)function[i] = '\0';
	for(i = 0; *instr != ' ';instr++,i++)function[i]= *instr;

	if (strcmp(function, "LW")==0 || strcmp(function, "SW")==0){
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

		if (strcmp(function,"LW")==0)LW(rt, offset, base, Tab, RAM);
		else if(strcmp(function,"SW")==0)SW(rt, offset, base, Tab, RAM);
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
			
			if (strcmp(function, "ADDI")==0){
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

			if (strcmp(function,"ADDI")==0)ADDI(rt, rs, offset, Tab);
			else if(strcmp(function,"BEQ")==0)BEQ(rs, rt, offset, Tab);
			else if(strcmp(function,"BNE")==0)BNE(rs, rt, offset, Tab);


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

			if (strcmp(function,"LUI")==0)LUI(rs, offset, Tab);
			else if(strcmp(function,"BGTZ")==0)BGTZ(rs, offset, Tab);
			else if(strcmp(function,"BLEZ")==0)BLEZ(rs, offset, Tab);
			
		}
	}
}

void J_instructionExecute(char *instr, char Tab[35][10]){

	/*the function convert a J-instruction in Hexadecimal*/

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
	if (strcmp(function,"J")==0)Jump(target, Tab);
	else if(strcmp(function,"JAL")==0)JAL(target, Tab);
}

void executeFile(char *source,char *destination,char Tab[35][10],char RAM[][4],char RAMinst[200][100]){

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
	int i,j;
	for(i = 0; i < N; i++) scriptLine[i] = '\0';
	for(i = 0; i < N; i++) instr[i] = '\0';
	for(i = 0; i < N; i++) hexa[i] = '\0';

	j = 0;
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
			strcpy(RAMinst[j],instr);
			fprintf(hexafile, "%s\n",hexa);
			for(i = 0; i < N; i++) instr[i] = '\0';
			for(i = 0; i < N; i++) hexa[i] = '\0';	
			j++;
		}
	}
	afficheRegistre(Tab);
	afficheRam(RAM);
	while(hexaToDecimal(Tab[34])/4 < j-2){
		//printf("%s\n", RAMinst[hexaToDecimal(Tab[34])/4]);
		instructionExecution(RAMinst[hexaToDecimal(Tab[34])/4], Tab, RAM);
	}
	afficheRegistre(Tab);
	afficheRam(RAM);
	fclose(scriptfile);
	fclose(hexafile);
}

void executeFilePasAPas(char *source,char *destination,char Tab[35][10],char RAM[][4],char RAMinst[200][100]){

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
	int i,j;
	for(i = 0; i < N; i++) scriptLine[i] = '\0';
	for(i = 0; i < N; i++) instr[i] = '\0';
	for(i = 0; i < N; i++) hexa[i] = '\0';

	j = 0;
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
			strcpy(RAMinst[j],instr);
			fprintf(hexafile, "%s\n",hexa);
			for(i = 0; i < N; i++) instr[i] = '\0';
			for(i = 0; i < N; i++) hexa[i] = '\0';	
			j++;
		}
	}
	char c;
	while(hexaToDecimal(Tab[34])/4 < j-2){
		instructionExecution(RAMinst[hexaToDecimal(Tab[34])/4], Tab, RAM);
		afficheRegistre(Tab);
		afficheRam(RAM);
		printf("On continue [o/n] : ");
		scanf("%c",&c);
		if (c == 'n')break;
	}
	fclose(scriptfile);
	fclose(hexafile);
}

void instructionExecution(char *instr,char Tab[35][10],char RAM[][4]){

	/*the function convert an instruction in Hexadecimal*/
	
	if (instructionType(instr)== R){
		R_instructionExecute(instr, Tab);
	}
	else if (instructionType(instr)== I){
		I_instructionExecute(instr, Tab, RAM);
	}
	else if (instructionType(instr)== J){
		J_instructionExecute(instr, Tab);
	}
	else if (instructionType(instr)== NOP);
	
	else{
		printf("ERROR\n");
	}
	initRegistre0(Tab);
}

void afficheRegistre(char Tab[35][10]){
	printf("R0:  %s",Tab[0]);
	printf("		R1:  %s\n",Tab[1]);
	printf("R2:  %s",Tab[2]);
	printf("		R3:  %s\n",Tab[3]);
	printf("R4:  %s",Tab[4]);
	printf("		R5:  %s\n",Tab[5]);
	printf("R6:  %s",Tab[6]);
	printf("		R7:  %s\n",Tab[7]);
	printf("R8:  %s",Tab[8]);
	printf("		R9:  %s\n",Tab[9]);
	printf("R10: %s",Tab[10]);
	printf("		R11: %s\n",Tab[11]);
	printf("R12: %s",Tab[12]);
	printf("		R13: %s\n",Tab[13]);
	printf("R14: %s",Tab[14]);
	printf("		R15: %s\n",Tab[15]);
	printf("R16: %s",Tab[16]);
	printf("		R17: %s\n",Tab[17]);
	printf("R18: %s",Tab[18]);
	printf("		R19: %s\n",Tab[19]);
	printf("R20: %s",Tab[20]);
	printf("		R21: %s\n",Tab[21]);
	printf("R22: %s",Tab[22]);
	printf("		R23: %s\n",Tab[23]);
	printf("R24: %s",Tab[24]);
	printf("		R25: %s\n",Tab[25]);
	printf("R26: %s",Tab[26]);
	printf("		R27: %s\n",Tab[27]);
	printf("R28: %s",Tab[28]);
	printf("		R29: %s\n",Tab[29]);
	printf("R30: %s",Tab[30]);
	printf("		R31: %s\n",Tab[31]);
	printf("LO:  %s\n",Tab[32]);
	printf("HI:  %s\n",Tab[33]);
	printf("PC:  %s\n",Tab[34]);
	printf("\n");
}

void initRegistre(char Tab[35][10]){
	int i,j;
	for(i=0;i<35;i++){
		for(j=0;j<8;j++)Tab[i][j]='0';
		Tab[i][8]='\0';
		Tab[i][9]='\0';
	}
}

void initRegistre0(char Tab[35][10]){
	int j;
	for(j=0;j<8;j++)Tab[0][j]='0';
	Tab[0][8]='\0';
	Tab[0][9]='\0';
}

void afficheRam(char RAM[100][4]){
	int i;
	for(i=0;i<100;i++){
		if(i % 4 == 3){
			if (i <10)printf("		@%d:  %s\n",i,RAM[i]);
			else printf("		@%d: %s\n",i,RAM[i]);
		}
		else if (i % 4 == 0){
			if (i <10)printf("@%d:  %s",i,RAM[i]);
			else printf("@%d: %s",i,RAM[i]);
		}
		
		else {
			if (i <10)printf("		@%d:  %s",i,RAM[i]);
			else printf("		@%d: %s",i,RAM[i]);
		}
	}
	printf("\n");
}

void initRam(char RAM[100][4]){
	int i,j;
	for(i=0;i<100;i++){
		for(j=0;j<2;j++)RAM[i][j]='0';
		RAM[i][2]='\0';
		RAM[i][3]='\0';
	}
}

int main(int argc, char *argv[]){
	char RAMinst[200][100];
	char RAM[100][4];
	char Tab[35][10];
	initRegistre(Tab);
	initRam(RAM);
	Tab[1][7]='F';
	Tab[2][7]='1';
	
	if (strcmp(argv[3],"-p"))executeFilePasAPas(argv[1],argv[2],Tab,RAM,RAMinst);
	else if(strcmp(argv[3],"-n"))executeFile(argv[1],argv[2],Tab,RAM,RAMinst);
	
}















































