/*
 * traverse.cpp
 *
 *  Created on: Dec 10, 2016
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
void travel(struct node_t * node, Stack *stackTest) {

	if (node == 0)
		return;

	cout << node->label << ": ";
// Inserting==============================================
	if (node->label == "vars") {

		cout << node->array[1].tokenInstance << "  ";
		stackTest->Insert(node->array[1].tokenInstance);
	}
	else if (node->label == "mvars") {
		cout << node->array[1].tokenInstance << "  ";
		stackTest->Insert(node->array[1].tokenInstance);

		// Verifying=======================================
	} else if (node->label == "R") {
		if (node->array[0].tokenID == "IDToken")
			if (!stackTest->Verify(node->array[0].tokenInstance))
			{
				cerr<<"First Instance of variable use "<<node->array[0].tokenInstance<< " in line "<<node->array[0].lineNumber<<endl;
				cerr<<"Fatal Error, Terminating"<<endl;
				exit(EXIT_FAILURE);
			}
	} else if (node->label == "in") {
		if (!stackTest->Verify(node->array[2].tokenInstance))
		{
			cerr<<"First Instance of variable use "<<node->array[2].tokenInstance<< " in line"<<node->array[2].lineNumber<<endl;
			cerr<<"Fatal Error, Terminating"<<endl;
			exit(EXIT_FAILURE);
		}
	} else if (node->label == "assign") {
		if (!stackTest->Verify(node->array[0].tokenInstance))
			{
			cerr<<"First Instance of variable use "<<node->array[0].tokenInstance<< " in line "<<node->array[0].lineNumber<<endl;
			cerr<<"Fatal Error, Terminating"<<endl;
			exit(EXIT_FAILURE);
			}
	}
	cout << endl;
	travel(node->list[0], stackTest);
	travel(node->list[1], stackTest);
	travel(node->list[2], stackTest);
	travel(node->list[3], stackTest);

}
