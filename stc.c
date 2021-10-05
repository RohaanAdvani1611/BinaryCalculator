#include<stdlib.h>
#include"stc.h"

// Stack implementation to store number list.

//Initialize stack
void iinit(istack *s) {
	*s = NULL;
}

//Add element to stack 
void ipush (istack *s, number *t) {
	istack temp;
	temp = (inode *)malloc(sizeof(inode));
	temp->a = t;
	temp->p = *s;
	*s = temp;
}

//Remove element from stack
number *ipop(istack *s) {
	number *t;
	istack temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->p;
	free(temp);
	return t;
}

//Check if stack is empty
int iisempty (istack *s) {
	return *s == NULL;
}


//  Stack implementation to store character Operators.

//Initialize stack
void cinit(cstack *s) {
	*s = NULL;
}

//Add element to stack
void cpush (cstack *s, char t) {
	cstack temp;
	temp = (cnode *)malloc(sizeof(cnode));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}

//Remove element from stack
char cpop(cstack *s) {
	char t;
	cstack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}

//Check if stack is empty
int cisempty (cstack *s) {
	return *s == NULL;
}

//Returns character on top
char ctop(cstack *s) {
	char ch;
	ch = cpop(s);
	cpush(s, ch);
	return ch;
}

