/*
 * token.h
 *
 *  Created on: Oct 12, 2016
 *      Author: Savaque
 */

#ifndef TOKEN_H_
#define TOKEN_H_
#include <string>

typedef struct token{
	std::string tokenID;
	std::string tokenInstance;
	int lineNumber;
}token;


#endif /* TOKEN_H_ */
