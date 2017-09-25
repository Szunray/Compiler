//============================================================================
// Name        : CompilerProject2.cpp
// Author      : Dillon Belton
// Version     :
// Copyright   : ain't got no copyright, steal away
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <streambuf>
#include "token.h"
#include "scanner.h"
#include <sstream>
#include <stdlib.h>
#include "parser.h"
#include "node_t.h"
#include "treePrint.h"
#include "stack.h"
#include "traverse.h"
#include "generate.h"
using namespace std;
//===========================================================================================
int main(int argc,char*argv[]) {

	char * fname;
	std::string test1=argv[1];
	test1+=".fs16";
	cout<< "testing" << test1<<endl;
		FILE *stream,*test;
		        if(argc!=2){// if there is no file argument, read from standard input
		                stream=stdin;
		                fname="keyboard";
		                ofstream myfile;
		                test=fopen("keyboard","a");
		                char i;
		                 while (fscanf(stream,"%d",&i)==1)
		                		{
		                		if(feof(stream))
		                		printf("feof identified");
		                		          printf("%c\n",i);
		                		fputc(i,test);
		                		 }
		                }
		        else{// if given a file argument , read the data from that file
				const char *mycharp=test1.c_str();
		                stream=fopen(mycharp,"r");// open a file stream
		                fname=argv[1];
		                }

		//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

		token Tok;

//===========================================================================================

		cout<<"Filename targeted is : " <<test1<< endl;
				const char *mycharp1=test1.c_str();
			  std::ifstream ifs(mycharp1);
			  std::string content( (std::istreambuf_iterator<char>(ifs) ),
			                       (std::istreambuf_iterator<char>()    ) );
			cout<<"File Contents were as follows :\n"<<content<<endl;
			cout<<"Scanning:"<<endl;

			// ==============================================================================
			cout<<"sending content to parser"<<endl;


			struct node_t* plswrk= parser(content);
			//treePrint(plswrk);


			//printTree(stuff);
			Stack stackTest;
			stackTest.index=0;
/*
		

		*/
			treePrint(plswrk,&stackTest);
			cout<< "\nNow Focusing in on Variable Declarations"<<endl;
			travel(plswrk,&stackTest);
			stackTest.printAll();
			FILE * fp;
			const char *mycharp=test1.c_str();
			generate(plswrk,mycharp,stackTest);

//===========================================================================================


		return 1;

}
