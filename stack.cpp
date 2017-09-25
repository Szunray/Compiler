/*
 * stack.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: Savaque
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
//#include "token.h"
using namespace std;
class Stack{
public:
	std::string test[100];
	int index;
	void Push(std::string);
	void Insert(std::string);
	int Find(std::string);
	void printAll();
	void printStop();
	bool Verify(std::string);

};

void Stack::Push(std::string str){
	if(index>=99){
		cerr<<"Stack Overflow"<<endl;
		exit(EXIT_FAILURE);
	}

	test[index]=str;
	index++;
	//cout<<"Index incremented to :" << index<<endl;

}
int Stack::Find(std::string str){
	for(int x=index;x>-1;x--){

		if (test[x]==str){
			return (index-x);
		}

	}
	return -1;
}
void Stack::Insert(std::string str){
	if(this->Find(str)==-1){
		//cout<<" Find returned "<<this->Find(str)<<endl;
		this->Push(str);
		//cout<<"this has " <<this->test[0]<< " as its first value"<<endl;
	}
	else{
		cerr<<"Redeclaration of Variable: "<<str<<endl;
		cerr<<"Fatal Error, Terminating"<<endl;
		exit(EXIT_FAILURE);

	}
}
bool Stack::Verify(std::string str){
	if(this->Find(str)==-1){
		return false;
	}
	else
		return true;
}
void Stack::printAll(){
	cout<<"Index is "<<index<<endl;
	cout<<"Printing Stack from Bottom"<<endl;
	for(int x=0;x<index;x++){
		cout<< "PUSH"<<endl;
		cout<<"LOAD "<< test[x]<<endl;
		cout<<"STACKW 0"<<endl;

	}
	cout<<endl;
}
void Stack::printStop(){
	for(int x=0;x<index;x++){
		cout<<test[x]<<" 0"<<endl;
	}
}
