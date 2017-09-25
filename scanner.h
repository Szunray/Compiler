/*
 * scanner.h
 *
 *  Created on: Oct 18, 2016
 *      Author: Savaque
 */

#ifndef SCANNER_H_
#define SCANNER_H_
#include <string>
#include "token.h"

void initializeScanner(void);
token Driver(std::string);
#endif /* SCANNER_H_ */
