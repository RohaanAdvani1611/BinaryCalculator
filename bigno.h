#include<stdio.h>
#include<stdlib.h>

//ADT for storing digit
typedef struct node {
	int data;
	struct node *next, *prev;
}node;

//ADT for storing entire number
typedef struct list {
	node *head, *tail;
	int len,sign;
}number;

void init(number *n);
void append(number *n, int d);
void traverse(number *n);
int remov(number *n, int pos);
void insert_beg(number *n, int d);
void insert_at(number *n, int i, int d);
void destroy(number *n);
int show(number *n, int pos);



