/*
 * stack.h
 *
 *  Created on: Dec 10, 2016
 *      Author: Savaque
 */

#ifndef STACK_H_
#define STACK_H_

class Stack{
public:
	std::string test[100];
	int index=0;
	void Push(std::string);
	void Insert(std::string);
	void printAll();
	void printStop();
	int Find(std::string);
	bool Verify(std::string);

};



#endif /* STACK_H_ */
