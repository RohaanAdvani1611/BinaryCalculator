#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "opr.h"

//Copy's one number into another
void copy(number *n1,number *n2){
    destroy(n1);
    node *p = n2->head;
    while (p){
        append(n1,p->data);
        p = p->next;
    }
    n1->sign = n2->sign;
    return ;
}

//Compare the two numbers wrt length and then wrt data is respective nodes
int compare(number *n1,number *n2) {
	//Check for empty
    if (n1->head == NULL)
        return -1;
    if (n2->head == NULL)
        return 1;
	zeroRemov(n1);
    zeroRemov(n2);
	//If empty
    if (n1->head == NULL)
        append(n1,0);
    if (n2->head == NULL)
        append(n2, 0);

    int lenA = n1->len;
    int lenB = n2->len;
	//Comparing lengths
    if (lenA > lenB) 
        return 1;
    
    else if (lenB > lenA) 
        return -1;
    
	//Comparing data in nodes
    node *p = n1->head;
    node *q = n2->head;
    while (p != NULL && q != NULL) {
        if (p->data > q->data)
            return 1;
        else if (p->data < q->data)
            return -1;
        p = p->next;
        q = q->next;
    }
    return 0;
}

//Performing addition of two numbers
number *addition(number *l1, number *l2) {
	number *result;
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	result = (number *)malloc(sizeof(number));
	init(result);
	//If sign different perform +ve or -ve subtraction 
	if(l1->sign != l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			result = subtraction(l2, l1);
		}
		else if(l2->sign == -1) {
			l2->sign = 1;
			result = subtraction(l1, l2);
		}
	}
	//If sign same perform addition of 2 +'ves/-'ves
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1)
			result->sign = -1;
		else
			result->sign = 1;
		int num = 0, i, j;
		i = l1->len;
		j = l2->len;
		//Initializecarry as zero
		int carry = 0;
		while(i != 0 || j != 0) {
			//If length of first number is 0
			if(i == 0) {
				num = show(l2, j - 1) + carry;
				j--;
				carry = num / 10;
				num = num % 10;
				//Update result
				insert_beg(result, num);
			}
			//If length of second number is 0
			else if(j == 0) {
				num = show(l1, i -1) + carry;
				i--;
				carry = num / 10;
				num = num % 10;
				//Update result
				insert_beg(result, num);
			}
			//Else both lengths are not zero
			else {
				num = show(l1, i - 1) + show(l2, j - 1) + carry;
				i--;
				j--;
				carry = num / 10;
				num = num % 10;
				//Update result
				insert_beg(result, num);
			}
		}
		//Loop will execute until both digits dont reach null
		//After loop is carry still exists add to begining of number
		if(carry != 0)
			insert_beg(result, carry);
	}
	l1->sign = sign1;
	l2->sign = sign2;
	zeroRemov(result);
	return result;
}

//Equates length of two numbers by adding 0's as preceding digits to the smaller number
void lengthEqual(number *n1, number *n2) {
	int gap;
	gap = n1->len - n2->len;
	if(gap > 0) {
		int i = 0;
		while(i < gap) {
		    //adding zeros to second number
			insert_beg(n2, 0);
			i++;
		}
	}
	else if(gap < 0) {
		int i = 0;
		gap = -gap;
		while(i < gap) {
			//adding zeros to first number
			insert_beg(n1, 0);
			i++;
		}
	}
}

//Performing subtraction of two numbers
number *subtraction(number *l1, number *l2) {
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;

	int num;
	int flag = 0;
	number *result;
	result = (number *)malloc(sizeof(number));
	init(result);
	//If sign is different perform +ve or -ve addition
	if(l1->sign != l2->sign) {
		if(l2->sign == -1) {
			l2->sign = 1;
			result = addition(l1, l2);
			result->sign = 1;
		}
		if(l1->sign == -1) {
			l1->sign = 1;
			result = addition(l1, l2);
			result->sign = -1;
		}
	}
	//If sign same perform subtraction
	else if(l1->sign == l2->sign) {
		//If first number negative reverse numbers for subtraction
		if(l1->sign == -1) {
			l1->sign = 1;
			l2->sign = 1;
			result = subtraction(l2, l1);
		}
		if(l1->sign == 1) {
			if(compare(l1, l2) >= 0) {
				if(flag != 1)
					result->sign = 1;
				else
					result->sign = -1;
				int b = 0;
				int m,n;
				m = l1->len - 1;
				n = l2->len - 1;
				while(m != -1 || n != -1) {
					if(n == -1) {
						num = show(l1, m);
						m--;
						insert_beg(result, num);
					}
					else {
						int a = show(l1, m);
						m--;
						int c = show(l2, n);
						n--;
						if(a >= c) {
							num = a - c;
							insert_beg(result, num);
						}
						else {
							int d = 0;
							while(!(b = remov(l1, m))) {
								m--;
								d++;
							}
							m--;
							m++;
							insert_at(l1, m, b - 1);
							int i;
							for(i = 0; i < d; i++) {
								m++;
								insert_at(l1, m, 9);
							}
							num = 10 + a - c;
							insert_beg(result, num);
						}
					}
				}
			}
			else if(compare(l1, l2) < 0) {
				flag = 1;
				result = subtraction(l2, l1);
				result->sign = -1;
			}
		}
	}
	flag = 0;
	l1->sign = sign1;
	l2->sign = sign2;
	zeroRemov(result);
	return result;
}

//Makes an empty list with 0's of mentioned size
void make_empty_list(number *newn,int size) {
    int i=0;
    while (i<size){
        insert_beg(newn,0);
        i++;
    }
}

//Remove all zeros preceding our number 
void zeroRemov(number *n){
    node *p = n->head;
    while (p){
        if (p->data == 0){
            p = p->next;
            remov(n,0);
        }
        else
            break;
    }
}

//Perform multiplication of two numbers
number* multiplication(number *n1,number *n2){
    number *multi;
    multi = (number*)malloc(sizeof(number));
    init(multi);

    int m = n1->len;
    int n = n2->len;
	//Make an empty list of size one more than the sum of lengths of two numbers that being the maximum possible size of a product
    make_empty_list(multi,m + n+1);

    node *ptr2 = n2->tail,*res_ptr1 = multi->tail, *res_ptr2, *ptr1;
    while (ptr2) {
        int carry = 0;
        res_ptr2 = res_ptr1;
        ptr1 = n1->tail;
		//loop for pointer 1 is inside that of pointer 2 as each digit is multiplied by each digit of both numbers
        while (ptr1) {
			//Multiply integer by integer adding carry
            int mul = ptr1->data * ptr2->data + carry;

            res_ptr2->data += mul % 10;

            carry = mul / 10 + res_ptr2->data / 10;
            res_ptr2->data = res_ptr2->data % 10;

            ptr1 = ptr1->prev;
            res_ptr2 = res_ptr2->prev;
        }

        if (carry > 0) {
            res_ptr2->data += carry;
        }

        res_ptr1 = res_ptr1->prev;
        ptr2 = ptr2->prev;
    }
	//If signs different resulting sign is -ve
    if ((n1->sign == -1 && n2->sign == 1) || (n2->sign == -1 && n1->sign == 1))
        multi->sign = -1;

    zeroRemov(multi);
    return multi;
}

//To check for zeros in a number 
int checkzero(number *l) {
	int e, flag = 0;
	node *p = l->head;

	while (p){
        if (p->data != 0)
            flag = 1;
        p = p->next;
	}
	return flag;
}

//Perform division between two numbers
number *division(number *l1, number *l2) {
	//Check division by 0
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:dividing by zero");
		return NULL;
	}
	number *result;
	result = (number *)malloc(sizeof(number));
	number *temp;
	temp = (number *)malloc(sizeof(number));
	init(temp);
	init(result);
	int m, sign1, sign2;
	//store signs of numbers and check sign of result wrt that
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}

    int num;

	for(int i = 0; i < l1->len; i++) {
		num = show(l1, i);
		append(temp, num);

		if(compare(temp, l2) < 0) {
			append(result, 0);

		}
		else {
			int d = 0;
			while(1) {
				temp = subtraction(temp, l2);

				d++;

				if(compare(temp, l2) < 0)
					break;

			}
			append(result, d);
			if (checkzero(temp) == 0)
                destroy(temp);
		}
	}

	l1->sign = sign1;
	l2->sign = sign2;
	zeroRemov(result);
	if (result->head == NULL)
        append(result,0);
	return result;
}

//Perform modulus function between two numbers
number *modulus(number *l1, number *l2) {
	//Check mod by 0
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:modulo by zero");
		return NULL;
	}
	number *result;
	result = (number *)malloc(sizeof(number));
	number *temp;
	temp = (number *)malloc(sizeof(number));
	init(temp);
	init(result);
	number *l3;
	l3 = (number *)malloc(sizeof(number));
	init(l3);
	copy(l3, l2);
	int m, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}

	int a, b;
	m = l1->len;
	int i, j, num;


	for(i = 0; i < l1->len; i++) {
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l3) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = subtraction(temp, l3);
				d++;
				if(compare(temp, l3) < 0)
					break;

			}
			append(result, d);
		}
	}
	l1->len = m;
	l1->sign = sign1;
	l2->sign = sign2;
	return temp;
}
