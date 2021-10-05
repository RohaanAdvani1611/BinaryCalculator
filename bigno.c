#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include "bigno.h"


//Initializing pointers to null, length to zero and sign to +'ve
void init(number *n) {
    n->head = NULL;
    n->tail = NULL;
    n->len = 0;
    n->sign = 1;
    return;
}


//Adding newnode at end of list as new digit
void append(number *n, int d){
    node *p, *newnode;
    newnode = (node*)malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
        newnode->prev = NULL;
    }
    else return;
    //Incase of empty list
    if(n->head == NULL){
        n->head = newnode;
        n->tail = newnode;
        n->len++;
        return;
    }
    //Incase of non empty list
    p = n->head;
    while(p -> next) {
       p = p->next;
    }
    p->next = newnode;
    newnode->prev = p;
    newnode->next = NULL;
    n->len++;
    n->tail = newnode;
    return;
}


//Printing the entire number
void traverse(number *n){
    node *p = n->head;
    //Check and print sign
    if (n->sign == -1)
        printf("-");
    while (p){
        printf("%d",p->data);
        p = p->next;
    }
    printf("\n");
    return;
}


//Remove chosen digit
int remov(number *n, int pos){
	int i;
	int data;
	node *p, *tmp;
	// handle errors on position 
	if(pos < 0 || pos >= n->len)
		return 0;
        if(n->head == NULL)
		return 0;
	
	p = n->head;
	for(i = 0; i < pos - 1; i++)
		p = p->next;
	if(n->len == 1) {
		data = p->data;
		n->head = n->tail = p = NULL;
		n->len--;
		return data;
	}
	//removing first digit
	if(pos == 0) {
		data = p->data;
		p->next->prev = NULL;
		n->head = p->next;
		free(p);
		n->len--;
		return data;
	}
	//removing last digit
	if(pos == n->len - 1) {
		data = p->next->data;
		tmp = p->next;
		p->next = NULL;
		n->tail = p;
		free(tmp);
		n->len--;
		return data;
	}

	tmp = p->next;
	p->next = p->next->next;
	tmp->next->prev = p;
	data = tmp->data;
	free(tmp);
	n->len--;
	return data;
}


//insert newnode of digit at beginning
void insert_beg(number *n, int d) {
    node *newnode;
    newnode = (node*)malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
        newnode->prev = NULL;
    }
    else return;
    if (n->head == NULL){
        n->head = newnode;
        n->tail = newnode;
        n->len++;
        return ;
    }
    node *p = n->head;

    newnode->next = p;
    p->prev = newnode;

    newnode->prev = NULL;

    n->head = newnode;
    n->len++;
}


//insert newnode of digit at index i
void insert_at(number *n, int i, int d){
    node  *newnode;
    newnode = (node*)malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
        newnode->prev = NULL;
    }
    else return;
    //if first position is chosen
    if( i == 0){
        insert_beg(n,d);
        return;
    }
    //if last position is chosen
    int s = n->len;
    if(i >= s){
        append(n,d);
        return;
    }
    node *p = n->head;
    int j = 0;
    while(j < i-1) {
        p = p->next;
        j++;
    }
    newnode->next = p->next;
    p->next = newnode;
    p->next->prev = newnode;
    newnode->prev = p;
    n->len++;
    return;
}


//free the number
void destroy(number *n) {
    node *p = n->head;
    node * q;
    q = p;
    while(p){
        p = p->next;
        free(q);
    }
    n->head = NULL;
    n->tail = NULL;
    n->len = 0;
    n->sign = 1;
    return ;
}


//print digit
int show(number *n, int pos) {
	node *p;
	//handle position errors
	if(pos <0 || pos > n->len)
		return 0;
	p = n->head;
	int i;
	for(i = 0; i < pos; i++)
		p = p->next;
	return p->data;
}
