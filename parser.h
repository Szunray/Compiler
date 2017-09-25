/*
 * parser.h
 *
 *  Created on: Nov 2, 2016
 *      Author: Savaque
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include "token.h"
#include "scanner.h"

struct node_t* parser(std::string);
struct node_t * getNode(std::string);
token tokopy(token);
void printTree(struct node_t*);
#endif /* PARSER_H_ */
