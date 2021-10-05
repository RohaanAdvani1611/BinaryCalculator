#include <stdio.h>
#include <stdlib.h>
#include "bigno.h"

int main(){
    printf("Welcome to my binary calculator \n");
    printf("It performs addition, subtraction, multiplication, division and modulus functions \n");
    printf("Brackets can also be used () \n");
    printf("Make sure to give space before and after each operator/bracket/operand \n");
    number *s1,*s2,*result;
    s1 = (number*)malloc(sizeof(number));
    s2 = (number*)malloc(sizeof(number));
    result = (number*)malloc(sizeof(number));
    init(s1);
    init(s2);
    init(result);

    char s[32];

    s1->sign = 1;
    s2->sign = 1;

    gets(s);
    result = infix(s);
    traverse(result);
}

