#include <stdio.h>
#include "stc.h"

//Provide each operator with a precedance value for deciding which operation to perform in which order
int precedance(char operator) {
	switch(operator) {
		//Closing bracket is given least precedance
		case ')' :
			return 0;
			break;
		case '+' :
		case '-' :
			return 1;
			break;
		case '*' :
		case '/' :
			return 2;
			break;
		case '%' :
			return 3;
			break;
		case '(' :
			return 4;
			break;
		default :
			return 5;
			break;
	}
	return 5;
}

//Providing an integeral value to each type of character
#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400

//Creating ADT token which we use in get token
typedef struct token{
	int type;
	number *num;
	char op;
}token;
//Enum is a user defined data type in C. It is mainly used to assign names to integral constants.
enum state { NUMBER, OP, FINISH, ERROR, SPC };


token gettoken(char *expr, int *reset) {
    static int i=0;
	number *n = (number *)malloc(sizeof(number));
	init(n);
	char currchar;
	//Initialize current state as space as its convinient
	static enum state currstate = SPC;
	enum state nextstate;
	token t;
	//Resets static int i to 0 for new expressions
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;
	}
	//Loop decides the next state depending on the case the state is selected
	while(1) {
		currchar = expr[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						nextstate = NUMBER;
						append(n, (int)currchar-'0');
						i++;
						break;
					case '+': case '-': case '*': case '/': 
					case '%': case '(' : case ')' :
						nextstate = OP;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						i++;
						return t;
						break;
					default: // anything else
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = n;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						t.type = OPERAND;
						nextstate = NUMBER;
						currstate = nextstate;
						if (expr[i-1] == '-')
                            n->sign = -1;
                        append(n,(int)currchar - '0');
						i++;
						break;
					case '+': case '-': case '*': case '/': 
					case '%': case '(' : case ')' :
						nextstate = OP;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					default: // anything else
						nextstate = ERROR;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						//no = currchar - '0';
						append(n, (int) currchar-'0');
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '!': 
					case '%': case '(' : case ')' :
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;
					default: // anything else
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}


number *infix(char *exp) {
	token t;
	char curr_op, prev_op, ch;
	//cnt_ob and cnt_cb and open and closed bracket counts respectively
	int cnt_ob = 0, cnt_cb = 0, reset  = 1, curr, prev;
	number *x, *y, *z;
	x = (number *)malloc(sizeof(number));
	y = (number *)malloc(sizeof(number));
	z = (number *)malloc(sizeof(number));
	init(x);
	init(y);
	init(z);
	istack is;
	cstack cs;
	iinit(&is);
	cinit(&cs);
	prev = ERR;
	while(1) {
		t = gettoken(exp, &reset); //Calling the gettoken func for all tokens in loop
		curr = t.type;
		if(curr == prev && prev == OPERAND) {
			//return INT_MIN;
			return NULL;
		}
		if(t.type == OPERAND)
			ipush(&is, t.num); //Push number in integer stack
		
		else if(t.type == OPERATOR){
			curr_op = t.op; //Current operator = token operator
			if(curr_op == '(') // Count open brackets
				cnt_ob++;
			if(curr_op == ')') // Count closed brackets
				cnt_cb++;
			if(cnt_cb > cnt_ob) //Number of closed brackets must always be less than that of open
				return NULL;
			if(!cisempty(&cs)) {
				prev_op = ctop(&cs);
				//Compare precedance of operators and update order of operations	
				while(precedance(prev_op) >= precedance(curr_op)) {
					prev_op = cpop(&cs);
					if(!iisempty(&is)) {
						x = ipop(&is);
					}
					else{
						cpush(&cs, prev_op);
						break;
					}
					if(!iisempty(&is)) {
						y = ipop(&is);
					}
					else {
						cpush(&cs, prev_op);
						ipush(&is, x);
						break;
					}
					//Division and modulus by 0 not permitted
					if((prev_op == '/' || prev_op == '%') && x == 0) {
                        printf("Mathematical error\n");
                        return NULL;
                    }
					//Perform operations by calling functions
					//Calculate result and push back to stack in each case
					switch (prev_op) {
						case '+' :
							//z = x + y;
							z = addition(x, y);
							ipush(&is, z);
							break;
						case '-' :
							//z = y - x;
							z = subtraction(y, x);
							ipush(&is, z);
							break;
						case '*' :
							//z = y * x;
							z = multiplication(y, x);
							ipush(&is, z);
							break;
						case '/' :
							//z = y / x;
							z = division(y, x);
							ipush(&is, z);
							break;
						case '%' :
							//z = y % x;
							z = modulus(y, x);
							ipush(&is, z);
							break;
						case '(' :
							cpush(&cs, prev_op);
							ipush(&is, y);
							ipush(&is, x);
							break;
						default :
							//return INT_MIN;
							return NULL;
					}
					if (prev_op == '(')
						break;
					if(!cisempty(&cs))
						prev_op = ctop(&cs);
					else
						break;
				}
			}
			cpush(&cs, t.op);
			//Once expression in brackets solved brackets are popped
			if(curr_op == ')') {
				ch = cpop(&cs);
				cnt_cb--;
				ch = cpop(&cs);
				cnt_ob--;
			}
		}
		else if(t.type == END) {
			//Make sure counts of brackets are equal
			if(cnt_ob == cnt_cb) {
				while(!cisempty(&cs)) {
					if(!iisempty(&is)) {
						x = ipop(&is);
					}
					else {
						printf("Less operands\n");
                        //return INT_MIN;
                        return NULL;
					}
					if(!iisempty(&is)) {
						y = ipop(&is);
					}
					else {
                        printf("Less operands\n");
                        //return INT_MIN;
                        return NULL;
					}
					ch = cpop(&cs);
					if((ch == '/' || ch == '%') && x == 0) {
						printf("Mathematical error\n");
						//return INT_MIN;
						return NULL;
					}
					switch(ch) {
						case '+' :
							z = addition(y, x);
							ipush(&is, z);
							break;
						case '-' :
							z = subtraction(y, x);
							ipush(&is, z);
							break;
						case '*' :
							z = multiplication(y, x);
							ipush(&is, z);
							break;
						case '/' :
							z = division(y, x);
							ipush(&is, z);
							break;
						case '%' :
							z = modulus(y, x);
							ipush(&is, z);
							break;

						default :
							//return INT_MIN;
							return NULL;
					}
				}
			}
			else {
				printf("Error in Expression\n");
				//return INT_MIN;
				return NULL;
			}
			if(!iisempty(&is)){
				z = ipop(&is);
				if(iisempty(&is))
					return z;
				else {
					printf("Less Operators\n");
                    //return INT_MIN;
                    return NULL;
                }
			}
			else {
				printf("Less Operands\n");
				return NULL;
			}
		}
		else if(t.type == ERR) {
			return NULL;
		}
		prev = curr;
	}
}


