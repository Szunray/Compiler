/*
 * treePrint.cpp
 *
 *  Created on: Nov 14, 2016
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
using namespace std;
void treePrint(struct node_t * node, Stack *stackTest){

		if(node==NULL)
			return;
		cout<<node->label<<": ";
		for(int x=0;x<4;x++){

			//cout<<node->array[x].tokenID<< " ";
			//stackTest->Push(node->array[x].tokenID);
			cout<<node->array[x].tokenInstance<< "  ";
		}
		cout<<endl;
		treePrint(node->list[0],stackTest);
		treePrint(node->list[1],stackTest);
		treePrint(node->list[2],stackTest);
		treePrint(node->list[3],stackTest);

	}
