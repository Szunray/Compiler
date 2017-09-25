/*
 * parser.cpp
 *
 *  Created on: Nov 2, 2016
 *      Author: Savaque
 */
#include <iostream>
#include "scanner.h"
#include "token.h"
#include <string>
#include <stdlib.h>
#include "node_t.h"
#include <stdio.h>
using namespace std;
std::string str;
token tok;

struct node_t* program();
struct node_t* block();
struct node_t* vars();
struct node_t* mVars();
struct node_t* expr();
struct node_t* M();
struct node_t* T();
struct node_t* F();
struct node_t* R();
struct node_t* stats();
struct node_t* mStat();
struct node_t* stat();
struct node_t* in();
struct node_t* out();
struct node_t* iff();
struct node_t* loop();
struct node_t* assign();
struct node_t* RO();

struct node_t *getNode(std::string name){
 struct node_t * temp= new node_t;



	temp->label=name;
	temp->list[0]=NULL;
	temp->list[1]=NULL;
	temp->list[2]=NULL;
	temp->list[3]=NULL;



	return temp;
}
token tokopy(token tok){
	token tokopy;
	tokopy.lineNumber=tok.lineNumber;
	tokopy.tokenID=tok.tokenID;
	tokopy.tokenInstance=tok.tokenInstance;
	return tokopy;
}

//------------------------------

struct node_t* parser(std::string content){
	str=content;
	struct node_t* root=getNode("root");
	tok=Driver(str);
	root->list[0]=program();
	if (tok.tokenID=="EOFToken"){
		cout<<"success!"<<endl;
		}
	else
		cout<<"error parser!"<<endl;
	token bigTest;
	bigTest.tokenID="Root Node";
	root->array[0]=bigTest;
return root;
}

struct node_t* program(){
	struct node_t * prgm=getNode("program");
	prgm->list[0]=vars();
	prgm->list[1]=block();
	return prgm;
}
struct node_t* block(){
	//cout<<"start of BLOCK"<<endl;
	if (tok.tokenID=="BeginToken")
	{
		struct node_t * blck=getNode("block");
		blck->array[0]=tokopy(tok);
		//cout<<blck->array[0].tokenID<<endl;
		tok=Driver(str);
		blck->list[0]=vars();
		blck->list[1]=stats();
		if(tok.tokenID=="EndToken")
		{
			blck->array[1]=tokopy(tok);
			tok=Driver(str);
		return blck;
		}
		else{
			cout<<"Error, Block. Line "<<tok.lineNumber <<endl;
			cerr<<"Fatal Error, Terminating"<<endl;
			exit(EXIT_FAILURE);
		}
	}
}

struct node_t* vars(){
	//cout<< "Start of VARS"<<endl;
	if(tok.tokenID=="VarToken")
	{
		struct node_t* vrs=getNode("vars");
		vrs->array[0]=tokopy(tok);
		tok=Driver(str);
		if (tok.tokenID=="IDToken")
		{
			vrs->array[1]=tokopy(tok);
			tok=Driver(str);

			vrs->list[0]=mVars();
			return vrs;
		}

		else{
			cout<<"Error, Vars. Line"<<tok.lineNumber <<endl;
					cerr<<"Fatal Error, Terminating"<<endl;
					exit(EXIT_FAILURE);
		}
	}
	else{
		//cout<<"End of Vars!"<<endl;
		return NULL;
	}
}

struct node_t* mVars(){
//cout<<"in mvars:"<<endl;
	if(tok.tokenID==":Token")
	{
		struct node_t* mvrs=getNode("mvars");
		mvrs->array[0]=tokopy(tok);
		tok=Driver(str);
		//cout<< "Token Type IS "<< tok.tokenID<<endl;
		if(tok.tokenID==":Token")
		{
			tok=Driver(str);
		}
		else
		{
			cout<<"Error, mVars. Line"<<tok.lineNumber <<endl;
								cerr<<"Fatal Error, Terminating"<<endl;
								exit(EXIT_FAILURE);
		}
		if(tok.tokenID=="IDToken")
		{
			mvrs->array[1]=tokopy(tok);
			tok=Driver(str);
			//cout<<"leaving mvars to go back into mvars"<<endl;
			//cout<< "The token I'm leaving with is"<<tok.tokenID<<endl;
			mvrs->list[0]=mVars();
			return mvrs;
		}
		else{
			cout<<"Error, mVars. Line"<<tok.lineNumber <<endl;
					cerr<<"Fatal Error, Terminating"<<endl;
					exit(EXIT_FAILURE);
		}
		//cout<<"token type" <<tok.tokenID<<endl;
		return NULL;
	}

	else{
		//tok=Driver(str);
		//tok=Driver(str);
		//cout<< "Test! Token is"<<tok.tokenID<<endl;
		//cout<<"leaving mvars"<<endl;
		return NULL;
	}

}
struct node_t* expr(){
	//cout<< "investigating expr"<<endl;
	struct node_t* exp=getNode("expr");
	exp->list[0]=M();
	if(tok.tokenID=="+Token")
	{
		exp->array[0]=tokopy(tok);
		tok=Driver(str);
		exp->list[1]=expr();
	}
		return exp;
}

struct node_t* M(){
	//cout<< "In M, still investigating"<<endl;
	struct node_t* Mptr=getNode("M");
	Mptr->list[0]=T();
	if(tok.tokenID=="-Token")
	{
		Mptr->array[0]=tokopy(tok);
		tok=Driver(str);
		Mptr->list[1]=M();
	}

		return Mptr;
}

struct node_t* F(){
	struct node_t* Fptr=getNode("F");
	if(tok.tokenID=="-Token")
	{
		Fptr->array[0]=tokopy(tok);
		tok=Driver(str);
		Fptr->list[0]=F();
	}

	else{
		Fptr->list[0]=R();
		if (Fptr->list[0]){
			//cout<<"Success, leaving F"<<endl;
			}
	}
	return Fptr;
}

struct node_t* T(){
	//cout<< "Made it to T"<<endl;
	struct node_t* Tptr=getNode("T");
	Tptr->list[0]=F();
	if(tok.tokenID=="*Token")
	{
		Tptr->array[0]=tokopy(tok);
		tok=Driver(str);
		Tptr->list[1]=T();
	}
	else if(tok.tokenID=="/Token")
	{
		Tptr->array[0]=tokopy(tok);
		tok=Driver(str);
		Tptr->list[1]=T();
	}
	if(Tptr->list[0]!=NULL){
		//cout<<"Success! leaving T"<<endl;
	}

		return Tptr;
}
struct node_t* R(){
	//cout<<"Made it to R"<<endl;
	struct node_t* Rptr=getNode("R");
	if(tok.tokenID=="[Token")
		{
			Rptr->array[0]=tokopy(tok);
			tok=Driver(str);
			Rptr->list[0]=expr();
			if(tok.tokenID=="]Token"){
				Rptr->array[1]=tokopy(tok);
				tok=Driver(str);
				return Rptr;
			}
			else
				cout<<"Error R!"<<endl;
		}
		else if(tok.tokenID=="IDToken")
		{
			Rptr->array[0]=tokopy(tok);
			tok=Driver(str);
			return Rptr;
		}
		else if(tok.tokenID=="numToken")
		{
			Rptr->array[0]=tokopy(tok);
			tok=Driver(str);
			//cout<<"leaving R"<<endl;
			return Rptr;
		}
	return Rptr;

}
struct node_t* stats(){
	//cout<< "Start of Stats"<<endl;
	struct node_t* sts=getNode("stats");
	sts->list[0]=stat();
	sts->list[1]=mStat();
	return sts;
	//cout<< "End of Stats"<<endl;
}
struct node_t* mStat(){
	//cout<<"Start Mstat!!"<<endl;
	struct node_t* mst=getNode("mStat");
	if(tok.tokenID=="ScanToken"||tok.tokenID=="PrintToken"||tok.tokenID=="[Token"||tok.tokenID=="LoopToken"||tok.tokenID=="IDToken"||tok.tokenID=="BeginToken"){
		mst->list[0]=stat();
		mst->list[1]=mStat();
	}
	else
	{
		//cout<<"Skipping MStat"<<endl;
		return NULL;
	}
	return mst;
}

struct node_t* stat(){
	//cout<< "this is Stat start"<<endl;
	//cout<<" I have tokenID "<<tok.tokenID<<endl;
	struct node_t* stt=getNode("stat");
	if(tok.tokenID=="ScanToken"){
		stt->list[0]=in();
	}
	else if(tok.tokenID=="PrintToken"){
		stt->list[0]=out();
	}
	else if(tok.tokenID=="BeginToken"){
		stt->list[0]=block();
	}
	else if(tok.tokenID=="[Token"){
		stt->list[0]=iff();
	}
	else if(tok.tokenID=="LoopToken"){
		stt->list[0]=loop();
	}
	else if(tok.tokenID=="IDToken"){
		stt->list[0]=assign();
	}
	else{
		cout<<"Error, Stat. Line"<<tok.lineNumber <<endl;
				cerr<<"Fatal Error, Terminating"<<endl;
				exit(EXIT_FAILURE);
	}
//cout<<"this is Stat End"<<endl;
return stt;
}

struct node_t* in(){
	struct node_t* nptr=getNode("in");
//cout<<"In ... well... IN!"<<endl;
		if(tok.tokenID=="ScanToken")
		{
			nptr->array[0]=tokopy(tok);
			tok=Driver(str);
			if(tok.tokenID==":Token")
			{
				nptr->array[1]=tokopy(tok);
				tok=Driver(str);
				if (tok.tokenID=="IDToken")
				{
					nptr->array[2]=tokopy(tok);
					tok=Driver(str);
					if(tok.tokenID==".Token")
					{
						nptr->array[3]=tokopy(tok);
						tok=Driver(str);
						return nptr;
					}

				}
			}

		}
		else{
			cout<<"Error, In. Line"<<tok.lineNumber <<endl;
					cerr<<"Fatal Error, Terminating"<<endl;
					exit(EXIT_FAILURE);
		}
}

struct node_t* out(){
	//cout<< "Start of Out"<<endl;
	struct node_t* optr=getNode("out");
	if(tok.tokenID=="PrintToken"){
		optr->array[0]=tokopy(tok);
		tok=Driver(str);
		if(tok.tokenID=="[Token"){
			optr->array[1]=tokopy(tok);
			tok=Driver(str);
			optr->list[0]=expr();// investigating
			if(tok.tokenID=="]Token"){
				optr->array[2]=tokopy(tok);
				tok=Driver(str);
				if(tok.tokenID==".Token")
								{
									optr->array[3]=tokopy(tok);
									tok=Driver(str);
									//cout<<"Leaving out with IDTOKEN"<<tok.tokenID<< endl;
									return optr;

								}
				cout<<"Error, Out. Line"<<tok.lineNumber <<endl;
						cerr<<"Fatal Error, Terminating"<<endl;
						exit(EXIT_FAILURE);
			}
		}
	}
	else{
		cout<<"Error, Out. Line"<<tok.lineNumber <<endl;
		cerr<<"Fatal Error, Terminating"<<endl;
		exit(EXIT_FAILURE);
	}

}

struct node_t* iff(){
	struct node_t* iffptr=getNode("iff");
	if(tok.tokenID=="[Token")
	{
		iffptr->array[0]=tokopy(tok);
		tok=Driver(str);
		iffptr->list[0]=expr();
		iffptr->list[1]=RO();
		iffptr->list[2]=expr();
		if(tok.tokenID=="]Token"){
			iffptr->array[1]=tokopy(tok);
			tok=Driver(str);
			if(tok.tokenID=="IffToken"){
				iffptr->array[2]=tokopy(tok);
				tok=Driver(str);
				iffptr->list[3]=block();
				return iffptr;
			}
		}
	}
	else{
		cout<<"Error, Iff. Line "<<tok.lineNumber <<endl;
		cerr<<"Fatal Error, Terminating"<<endl;
		exit(EXIT_FAILURE);
	}
}

struct node_t* loop(){
	//cout<<"inside Loopp!"<<endl;
	struct node_t* looptr=getNode("loop");
	if(tok.tokenID=="LoopToken")
	{
		looptr->array[0]=tokopy(tok);
		tok=Driver(str);
		if (tok.tokenID=="[Token"){
			looptr->array[1]=tokopy(tok);
			looptr->list[0]=expr();
			looptr->list[1]=RO();
			looptr->list[2]=expr();
			if(tok.tokenID=="]Token")
			{
				looptr->array[2]=tokopy(tok);
				tok=Driver(str);
			looptr->list[4]=block();
			return looptr;
			}
		}
	}
	else{
		cout<<"ERROR in LOOP!"<<tok.lineNumber <<endl;
		cerr<<"Fatal Error, Terminating"<<endl;
		exit(EXIT_FAILURE);
	}
}

struct node_t* assign(){
	struct node_t* ass=getNode("assign");
	if(tok.tokenID=="IDToken"){
		ass->array[0]=tokopy(tok);
		tok=Driver(str);
		if(tok.tokenID=="==Token")
		{
			ass->array[1]=tokopy(tok);
			tok=Driver(str);
			ass->list[0]=expr();
			if(tok.tokenID==".Token"){
				ass->array[2]=tokopy(tok);
				tok=Driver(str);
				return ass;
			}

		}
	}
	else{
		cout<<"Error, Assign. Line"<<tok.lineNumber <<endl;
		cerr<<"Fatal Error, Terminating"<<endl;
			exit(EXIT_FAILURE);
	}
}

struct node_t* RO(){
	struct node_t* ROptr=getNode("RO");
	ROptr->array[0]=tokopy(tok);
	if(tok.tokenID==">=>Token")
		tok=Driver(str);
	else if(tok.tokenID=="<=<Token")
		tok=Driver(str);
	else if(tok.tokenID=="=Token")
			tok=Driver(str);
	else if(tok.tokenID=="relationalToken")
			tok=Driver(str);
	else if(tok.tokenID=="=!=Token")
			tok=Driver(str);
	else{
		cout<<"Error, RO. Line "<<tok.lineNumber <<endl;
		cerr<<"Fatal Error, Terminating"<<endl;
					exit(EXIT_FAILURE);
	}
	return ROptr;
}


