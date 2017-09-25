/*
 * node_t.h
 *
 *  Created on: Nov 12, 2016
 *      Author: Savaque
 */

#ifndef NODE_T_H_
#define NODE_T_H_
#include <string.h>
#include "token.h"
struct node_t{
	std::string label;
	token array[4];
	node_t *list[4];
};



#endif /* NODE_T_H_ */
