
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "token.h"

static int scannerIndex=0;
static int lineNumber=1;
static int errFlag=0;//make an errflag cleared by whitespace characters to solve <<< problem
static int table[40][128];// 3 stages, and 128 ascii values;
using namespace std;

void initializeScanner() {

	int stage=0;

	//------------------------------------------------------Begin making table.


	for(int x=0;x<128;x++)
		table[0][x]=-1;//error code is -1;
		table[0][0]=999;
		table[0][32]=0;
		table[0][10]=0;
	// First stage/getting rolling. Stage 0. C

	for(int x=65;x<91;x++)
		table[0][x]=1;
	for(int x=97;x<123;x++)
			table[0][x]=1;// If Letter found, move to stage 1
	for(int x=48;x<57;x++)
			table[0][x]=2;// If Number, Move to stage 2;



	table[0][47]=22;// divide symbol
	table[0][42]=21;//*
	table[0][43]=20;//+
	table[0][45]=19;//-
	table[0][38]=3;//&
	table[0][37]=3;//%
	table[0][58]=17;//:


	table[0][60]=11;//<
	table[0][62]=12;//>
	//table[0][33]=4;// Is exclamation point "!" but, to be relational, must be sandwhiched between "="

	// Delimiters
	table[0][59]=5;//;
	table[0][46]=25;//.
	table[0][44]=5;//,
	table[0][40]=5;//(
	table[0][41]=5;//)
	table[0][123]=5;//{
	table[0][125]=5;//}
	table[0][91]=23;//[
	table[0][93]=24;//]

	// if start of comment, go to stage 6
	table[0][64]=6;
	// = sign processing
	table[0][61]=7;

	// s1, assuming it began with a letter, is trying to construct Identifier token.
	for(int x=0;x<129;x++)
		table[1][x]=1001;// set everything that isn't another letter or number to indicate an ERR token
	for(int x=65;x<90;x++)// Overlaying previous declarations so that numbers and digits loop back into stage 1.
			table[1][x]=1;
		for(int x=97;x<122;x++)
				table[1][x]=1;
		for(int x=48;x<57;x++)
				table[1][x]=1;
		table[1][32]=1001;
		table[1][10]=1001;
		table[1][0]=1001;

		//s2, assuming it began with a number, is trying to construct number token.
		for(int x=0;x<129;x++)
			table[2][x]=1002;// set everything that isn't another number to indicate an ERR token
			for(int x=48;x<57;x++)//loop around if its another digit
					table[2][x]=2;
			table[2][10]=1002;
			table[2][0]=1002;
			table[2][32]=1002;


		//s3 for Operators

		for(int x=0;x<129;x++)
			table[3][x]=1003;// set everything to lead to termination.
		table[3][10]=1003;
		table[3][0]=1003;
		table[3][32]=1003;

		//s4 for Relational operators
		for(int x=0;x<129;x++)
			table[4][x]=1004;
			table[4][32]=1004;
			table[4][10]=1004;//newline
			table[4][0]=1004;//eof
		table[4][60]=11;
		table[4][62]=12;
		// Dunno how to handle "=" So moving on to delimiters for now

		//s5 for Delimiters
		for(int x=0;x<129;x++)
			table[5][x]=1005;// set everything to lead to termination.
			table[5][32]=1005;
			table[5][10]=1005;
			table[5][0]=1005;
		//s6 for Comments
		for(int x=0;x<129;x++)
			table[6][x]=6;
		table[6][32]=1006;
		table[6][10]=1006;
		table[6][0]=1006;
		// s7 and s8 are processing = signs
		for(int x=0;x<129;x++)
					table[7][x]=-1;
		table[7][32]=1007;// = and a space
		table[7][10]=1007;// = and a space
		table[7][0]=1007;// = and a space
		table[7][61]=10;// turns our these need to be completed in their own stage;
		table[7][33]=8;
		//
		for(int x=0;x<129;x++)
					table[8][x]=-1;
		table[8][61]=9;
		for(int x=0;x<129;x++)
			table[9][x]=1009;// =!=
			table[9][32]=1009;
			table[9][10]=1009;
			table[9][0]=1009;
		for(int x=0;x<129;x++)
			table[10][x]=1008;//==
			table[10][32]=1008;
			table[10][10]=1008;
			table[10][0]=1008;
		//s11 is processing relational operators <= and
		for(int x=0;x<129;x++)
			table[11][x]=1004;
			table[11][32]=1004;
			table[11][10]=1004;
			table[11][0]=1004;
		table[11][61]=13;
		//s12 is >=
		for(int x=0;x<129;x++)
			table[12][x]=1004;
		table[12][32]=1004;
		table[12][10]=1004;
		table[12][0]=1004;
		table[12][61]=14;
		//s13 <=<
		for(int x=0;x<129;x++)
			table[13][x]=-1;
		table[13][60]=15;
		//s14 >=>
		for(int x=0;x<129;x++)
			table[14][x]=-1;
		table[14][62]=16;
		//s15 and s16 Done
		for(int x=0;x<129;x++)
			table[15][x]=1004;
			table[15][10]=1004;
			table[15][0]=1004;
			table[15][32]=1004;
		for(int x=0;x<129;x++)
			table[16][x]=1004;
			table[16][10]=1004;
			table[16][0]=1004;
			table[16][32]=1004;

			for(int x=0;x<129;x++)// :
						table[17][x]=1007;
						table[17][10]=1017;
						table[17][0]=1017;
						table[17][32]=1017;
						table[17][58]=18;
			for(int x=0;x<129;x++)// ::
						table[18][x]=1010;
						table[18][10]=1010;
						table[18][0]=1010;
						table[18][32]=1010;
			for(int x=0;x<129;x++)// -
						table[19][x]=1011;
						table[19][10]=1011;
						table[19][0]=1011;
						table[19][32]=1011;
			for(int x=0;x<129;x++)// -
						table[20][x]=1012;
						table[20][10]=1012;
						table[20][0]=1012;
						table[20][32]=1012;
			for(int x=0;x<129;x++)// *
						table[21][x]=1013;
						table[21][10]=1013;
						table[21][0]=1013;
						table[21][32]=1013;
			for(int x=0;x<129;x++)// divide
						table[22][x]=1014;
						table[22][10]=1014;
						table[22][0]=1014;
						table[22][32]=1014;

			for(int x=0;x<129;x++)// [
						table[23][x]=1015;
						table[23][10]=1015;
						table[23][0]=1015;
						table[23][32]=1015;
			for(int x=0;x<129;x++)// [
						table[24][x]=1016;
						table[24][10]=1016;
						table[24][0]=1016;
						table[24][32]=1016;
			for(int x=0;x<129;x++)// [
						table[25][x]=1018;
						table[25][10]=1018;
						table[25][0]=1018;
						table[25][32]=1018;
// --------------------------------------------- Table Made
//---testing

		// Construct the driver before deciding how to like, "stop" and actually produce error tokens.

}

token Driver(string str){
	initializeScanner();
	string tokenI;
	string tokeType;

	char *cstr= new char[str.length()+1];
	strcpy(cstr,str.c_str());// I did this to get the white space character at the end of the file/line

	int stage=0,next=0;//stage & next reset
	for (scannerIndex;scannerIndex<strlen(cstr)+1;scannerIndex++)
	{
		if(next==10)
			{
			lineNumber++;

			}
		// Check to see if the current token instance being worked on is a reserved word.
		// Decided to just brute force it here. This was gonna be done one way or the other.
		//Have it in a big chunk. Token types >20 are reserved word tokens.
		if(tokenI=="Begin"&& (int)cstr[scannerIndex]==32||(tokenI=="Begin"&& (int)cstr[scannerIndex]==10)){
			////cout<< "Completed BeginToken"<<endl;
			tokeType="BeginToken";
			//////cout<<tokenI<<endl;
			break;

		}
		if(tokenI=="End"&& (int)cstr[scannerIndex]==32||(tokenI=="End"&& (int)cstr[scannerIndex]==10)||(tokenI=="End"&& (int)cstr[scannerIndex]==0)){
					////cout<< "Completed EndToken"<<endl;
					tokeType="EndToken";
					////cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Start"&& (int)cstr[scannerIndex]==32||(tokenI=="Start"&& (int)cstr[scannerIndex]==10)){
					////cout<< "Completed StartToken"<<endl;
					tokeType="StartToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Stop"&& (int)cstr[scannerIndex]==32||(tokenI=="Stop"&& (int)cstr[scannerIndex]==10)){
					////cout<< "Completed StopToken"<<endl;
					tokeType="StopToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Iff"&& (int)cstr[scannerIndex]==32||(tokenI=="Iff"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed IffToken"<<endl;
					tokeType="IffToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Loop"&& (int)cstr[scannerIndex]==32||(tokenI=="Loop"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed LoopToken"<<endl;
					tokeType="LoopToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Void"&& (int)cstr[scannerIndex]==32||(tokenI=="Void"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed VoidToken"<<endl;
					tokeType=26;
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Var"&& (int)cstr[scannerIndex]==32||(tokenI=="Var"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed VarToken"<<endl;
					tokeType="VarToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Int"&& (int)cstr[scannerIndex]==32||(tokenI=="Int"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed IntToken"<<endl;
					tokeType="IntToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Call"&& (int)cstr[scannerIndex]==32||(tokenI=="Call"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed CallToken"<<endl;
					tokeType="CallToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Return"&& (int)cstr[scannerIndex]==32||(tokenI=="Return"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed ReturnToken"<<endl;
					tokeType="ReturnToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Scan"&& (int)cstr[scannerIndex]==32||(tokenI=="Scan"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed ScanToken"<<endl;
					tokeType="ScanToken";
					//cout<<tokenI<<endl;
					break;

				}
		if(tokenI=="Print"&& (int)cstr[scannerIndex]==32||(tokenI=="Print"&& (int)cstr[scannerIndex]==10) ){
					//cout<< "Completed PrintToken"<<endl;
					tokeType="PrintToken";
					//cout<<tokenI<<endl;
					break;

				}
		if((tokenI=="Program"&& (int)cstr[scannerIndex]==32)||(tokenI=="Program"&& (int)cstr[scannerIndex]==10)){
					//cout<< "Completed ProgramToken"<<endl;
					tokeType="ProgramToken";
					//cout<<tokenI<<endl;
					break;

				}
		// All of the Reserved Words are now out of the way.

		////cout<<"Character being evaluated : " << cstr[scannerIndex]<<"   Ascii Value: "<< (int)cstr[scannerIndex]<<endl;
		next=(int)cstr[scannerIndex];// next is the ascii value of the character being evaluated
		if(table[stage][next]==-1){
			//cout<<"ERROR"<<endl;
			tokeType="ERR";
			scannerIndex++;
					break;
		}
		if (table[stage][next]==0)
		{}
		else if(table[stage][next]<900){// see what the current stage says about how to handle this character
			tokenI+=cstr[scannerIndex];
			////cout<<tokenI<<endl;
			stage=table[stage][next];
			////cout<<stage<<endl;
		}

		else if(table[stage][next]==1001){
			//cout<<"Completed ID Token"<<endl;
			//cout<<tokenI<<endl;
			tokeType="IDToken";
			break;
		}
		else if(table[stage][next]==1002){
			//cout<<"Completed numToken"<<endl;
			tokeType="numToken";
			break;
						}
		else if(table[stage][next]==1003){
			//cout<< "Completed opToken"<<endl;
			tokeType="opToken";
			break;
		}
		else if(table[stage][next]==1004){
					//cout<< "Completed relationalToken"<<endl;
					//cout<<tokenI<<endl;
					tokeType="relationalToken";
					break;
				}
		else if(table[stage][next]==1005){
					//cout<< "Completed delimToken"<<endl;
					//cout<<tokenI<<endl;
					tokeType="delimToken";
					break;
				}
		else if(table[stage][next]==1006){
							//cout<< "Completed commToken"<<endl;
							//cout<<tokenI<<endl;
							tokeType="commToken";
							break;
						}
		else if(table[stage][next]==1007){
									//cout<< "Completed =Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="=Token";
									break;
								}
		else if(table[stage][next]==1008){
									//cout<< "Completed ==Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="==Token";
									break;
								}
		else if(table[stage][next]==1009){
									//cout<< "Completed =!=Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="=!=Token";
									break;
								}
		else if(table[stage][next]==1010){
									//cout<< "Completed ::Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="::Token";
									break;
								}
		else if(table[stage][next]==1011){
									//cout<< "Completed -Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="-Token";
									break;
										}
		else if(table[stage][next]==1012){
									//cout<< "Completed +Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="+Token";
									break;
										}
		else if(table[stage][next]==1013){
									//cout<< "Completed *Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="*Token";
									break;
										}
		else if(table[stage][next]==1014){
									//cout<< "Completed /Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="/Token";
									break;
										}
		else if(table[stage][next]==1015){
									//cout<< "Completed [Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="[Token";
									break;
										}
		else if(table[stage][next]==1016){
									//cout<< "Completed ]Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType="]Token";
									break;
										}
		else if (table[stage][next]==1017)
									{
									//cout<<"Completed :Token"<<endl;
									//cout<<tokenI<<endl;
									tokeType=":Token";
									break;
									}
		else if (table[stage][next]==1018)
											{
											//cout<<"Completed .Token"<<endl;
											//cout<<tokenI<<endl;
											tokeType=".Token";
											break;
											}
		else if(table[stage][next]==999){
									//cout<< "Completed EOFToken"<<endl;
									//cout<<tokenI<<endl;
									tokeType="EOFToken";
									break;
								}
	}
	token Result ={
			tokeType,
			tokenI,
			lineNumber,
	};
return Result;
}
