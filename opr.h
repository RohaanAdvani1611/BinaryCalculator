#include<stdio.h>
#include<stdlib.h>
#include "bigno.h"

void copy(number *n1, number *n2);
int compare(number *n1, number *n2);
number* addition(number *n1, number *n2);
void lengthEqual(number *n1, number *n2);
number* subtraction(number *n1, number *n2);
void make_empty_list(number *newn, int size);
void zeroRemov(number *n);
number* multiplication(number *n1, number *n2);
int checkzero(number *n);
number *division(number *n1, number *n2);
number *modulus(number *n1, number *n2);



