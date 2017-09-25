/*
 * generate.cpp
 *
 *  Created on: Dec 11, 2016
 *      Author: Savaque
 */
#include <iostream>
#include "scanner.h"
#include "token.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "node_t.h"
#include "stack.h"
#include <fstream>
using namespace std;

int temporary=0;
int label=0;
void generate(struct node_t* node, const char *fp, Stack stack){
	if(node==NULL)
		return;
	/*cout<<node->label<<": ";
	for(int x=0;x<4;x++){
		cout<<node->array[x].tokenID<< " ";
		//stackTest->Push(node->array[x].tokenID);
		cout<<node->array[x].tokenInstance<< "  ";
	}*/
	if (node->label=="vars"){
		//cout<<"LOAD "<<node->array[1].tokenInstance<<endl;
	//printf("LOAD %s \n",node->array[1].tokenID);
	}
	if (node->label=="mvars"){
	//	cout<<"LOAD "<<node->array[1].tokenInstance<<endl;
	}

	if(node->label=="in"){

	}
	if (node->label=="assign"){

	}
	if (node->label=="F"){

	}
	/*if(node->label=="out"){
		cout<< "<Out>"<<endl;
		generate(node->list[0],fp,stack);
		generate(node->list[1],fp,stack);
		generate(node->list[2],fp,stack);
		generate(node->list[3],fp,stack);
		cout<<"STORE Temp"<<endl;
		cout<<"WRITE Temp"<<endl;
		cout<<"// <Out>"<<endl;
	}*/

	if(node->label=="root"){
		freopen("output.asm","w",stdout);
		//cout<< "This is the root node. My child nodes are ";
		//cout<<node->list[0]->label<<endl;

		//cout<<node->list[1]->label<<endl;
	generate(node->list[0],fp,stack);
	generate(node->list[1],fp,stack);
	generate(node->list[2],fp,stack);
	generate(node->list[3],fp,stack);
	}
	if (node->label=="program"){
		//cout<< "<program>. My child nodes are ";
		//cout<<node->list[0]->label<<" ";
			//	cout<<node->list[1]->label<<endl;
		generate(node->list[0],fp,stack);
			generate(node->list[1],fp,stack);
			generate(node->list[2],fp,stack);
			generate(node->list[3],fp,stack);
			cout<<"STOP"<<endl;
			for(int t=0;t<temporary;t++){
				cout<<"temp"<<t<<" 0"<<endl;
			}
			stack.printStop();
			return;
	}
	if(node ->label=="vars"){
		//cout<< "<vars> "<<endl;
		return;
	}
	if(node->label=="block"){
		//cout<<"<block>"<<endl;
		if(node->list[0])
			generate(node->list[0],fp,stack);
		if(node->list[1])
			generate(node->list[1],fp,stack);

		return;
	}
	if(node->label=="stats"){
		//cout<<"<stats>"<<endl;
		generate(node->list[0],fp,stack);
		generate(node->list[1],fp,stack);
		return;
	}
	if(node->label=="stat"){
		//cout<<"<stat> BIG TEST COMING UP"<<endl;
		generate(node->list[0],fp,stack);
		return;
	}
	if(node->label=="mStat"){
		//cout<<"<mStat>"<<endl;
		if(node->list[0]==NULL)
		return;
		else{
			generate(node->list[0],fp,stack);
			generate(node->list[1],fp,stack);
		}
	}
	if(node->label=="expr"){
		//cout<<"<expr>"<<endl;
		if(node->list[1]==NULL)
		{
			generate(node->list[0],fp,stack);
			return;
		}
		else{
			int temp=temporary;
			temporary++;
			generate(node->list[0],fp,stack);
			cout<<"STORE temp"<<temp<<endl;
			generate(node->list[1],fp,stack);
			cout<<"ADD temp"<<temp<<endl;
			return;
		}
	}
	if(node->label=="M"){
		//cout<<"<M>"<<endl;
		if(node->list[1]==NULL){
			generate(node->list[0],fp,stack);
		}
		else{
			//cout<<"M Gen"<<endl;
			int temp=temporary;
			temporary++;
			generate(node->list[1],fp,stack);
						cout<<"STORE temp"<<temp<<endl;
						generate(node->list[0],fp,stack);
						cout<<"SUB temp"<<temp<<endl;
						//cout<<"M end"<<endl;
						return;
		}
		return;
	}
	if(node->label=="T"){
	//	cout<< "<T>"<<endl;
		if(node->list[1]==NULL){
					generate(node->list[0],fp,stack);
				}
				else{
					int temp=temporary;
					temporary++;
					generate(node->list[1],fp,stack);
					cout<<"STORE temp"<<temp<<endl;
					generate(node->list[0],fp,stack);
					if(node->array[0].tokenID=="*Token")
					{
						//cout<<"Mult Case"<<endl;
						cout<<"MULT temp"<<temp<<endl;
					}
					else
						cout<<"DIV temp"<<temp<<endl;
					return;
				}
	}
	if(node->label=="F"){
	//	cout<<"<F>"<<endl;
			generate(node->list[0],fp,stack);
			if(node->array[0].tokenID=="-Token")
			cout<<"MULT -1"<<endl;

	}
	if(node->label=="R"){
	//	cout<<"<R>"<<endl;
		if(node->list[0]==NULL)
		{
			cout<<"LOAD "<<node->array[0].tokenInstance<<endl;

	}
		else{
			generate(node->list[0],fp,stack);
		}
			return;
		}

	if(node->label=="in"){
		cout<<"READ "<<node->array[2].tokenInstance<<endl;
		return;
	}
	if(node->label=="out"){
		int temp=temporary;
		temporary++;
		generate(node->list[0],fp,stack);
		cout<<"STORE temp"<<temp<<endl;
		cout<<"WRITE temp"<<temp<<endl;
	}
	if(node->label=="assign"){
		//cout<<"<assign"<<endl;
		generate(node->list[0],fp,stack);
		cout<<"STORE "<<node->array[0].tokenInstance<<endl;
	}
	if(node->label=="iff"){
		int temp=temporary;
		temporary++;
		int labelno=label;
		label++;
		generate(node->list[2],fp,stack);
		cout<<"STORE temp"<<temp<<endl;
		generate(node->list[0],fp,stack);
		cout<<"SUB temp"<<temp<<endl;
		string str=node->list[1]->array[0].tokenInstance;
		if(str=="<"){
			cout<<"BRZPOS label"<<labelno<<endl;
		}
		if(str==">"){
					cout<<"BZRNEG label"<<labelno<<endl;
				}
		if(str==">=>")
		{
			cout<<"BRNEG label"<<labelno<<endl;
		}
		if(str=="<=<")
				{
					cout<<"BRPOS label"<<labelno<<endl;
				}


		generate(node->list[3],fp,stack);
		cout<<"label"<<labelno<<": NOOP"<<endl;



	}


}
