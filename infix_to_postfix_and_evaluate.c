#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NEWL printf("\n");

// to store the main expression
char main_exp[100] ;
char new_exp[100] ;

struct stack
{
	char data[50];
	int c;
}op ;
struct istack
{
	int data[50];
	int c;
}val ;

void push(char a);
char pop();
void ipush(int a);
int ipop();
char top();
void infix_to_postfix(char *a);
int priority_check(char a,char b);
int priority_value(char a);
int empty_till_parentheses(char *ptr,int i);
int evaluate();
int multiply();
int divide();
int add();
int subtract();
int exponent();

void main()
{
	// initialise the stack
	op.c = -1;

	// input the string
	char *ptr = main_exp;
	scanf("%s",ptr);
	infix_to_postfix(ptr);
	printf("new exp:%s",new_exp);
	int ans = evaluate();
	printf("\nANSWER=>%d\n",ans);

}

void push(char a)
{
	op.c++ ;
	op.data[op.c] = a ;
}
char pop()
{
	op.c-- ;
	return (char)op.data[(op.c)+1] ;
}
void ipush(int a)
{
	val.c++ ;
	val.data[val.c] = a ;
}
int ipop()
{
	val.c-- ;
	return val.data[(val.c)+1] ;
}
char top()
{
	return op.data[op.c];
	// pass
}
void infix_to_postfix(char *ptr)
{
	int i = 0; // counter for new_exp

	while((*ptr) != '\0')
	{
		switch(*ptr)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':*(new_exp+i) = *ptr;
				     i++ ;
					 ptr++;
					 break;
			case '(':push('(');
					 ptr++;
					 break;
			case '^':
			case '*':
			case '/':
			case '+':
			case '-':if (op.c == -1) // stack is empty
					{
					    push(*ptr);
						ptr++;
					}
					else if (top()=='(') // topmost element of stack is opening parentheses
					{
						push(*ptr);
						ptr++;
					}
					else if( priority_check(top(),*ptr) ) // if priority of current operator is higher then this code executes
					{
						push(*ptr);
						ptr++;
					}
					else if( priority_check(*ptr,top()) ) // if priority of already stack operator is higher then this code executes
					{
						*(new_exp+i) = pop();
						push(*ptr);
						i++;
						ptr++;
					}
					else
					{//pass
					}
					break;
			case ')': i = empty_till_parentheses(ptr,i);
					  ptr++;
					  break;
			default: break;
		}
	}

	while(op.c != -1)
	{
		*(new_exp + i) = pop();
		i++;
	}
	*(new_exp+i) = '\0';
}
int priority_check(char a,char b)
{
	// returns 0 or 1 if priority of a or b is higher repectively
	int a_p = priority_value(a);
	int b_p = priority_value(b);

	// case of hgher or equal priority
	if (a_p >= b_p)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int priority_value(char a)
{
	switch(a)
	{
		case '^':
		return 5;
		case '*':
		return 4;
		case '/':
		return 3;
		case '+':
		return 2;
		case '-':
		return 1;
	}
}
int empty_till_parentheses(char *ptr,int i)
{
	char temp = pop();
	while(temp!='(')
	{
		*(new_exp+i) = temp;
		i++;
		temp = pop();
	}
	return i;
}
int evaluate()
{
	char *ptr = new_exp;
	int x;
	int t;
	// integer stack is intialised
	val.c = -1;
	//label
	do_again:
	if (*ptr == '\0')
	{
		t = ipop(); /*printf("\nReturning Anwser: %d",t);*/
		return(t);
	}
	while( (*ptr) != '*' && (*ptr) != '/' && (*ptr) != '+' && (*ptr) != '-' && (*ptr) != '^')
	{
		x = (*ptr) - '0' ;
		/*printf("\nPushing: %d",x);*/
		ipush((int)x);
		ptr++;
	}
	switch(*ptr)
	{
		case '*':t = multiply(); ipush(t); /*printf("\nPushing Multiply: %d",t);*/ptr++;
		break;
		case '/':t = divide(); ipush(t); /*printf("\nPushing Divide: %d",t)*/;ptr++;
		break;
		case '+':t = add(); ipush(t); /*printf("\nPushing Add: %d",t);*/ptr++;
		break;
		case '-':t = subtract(); ipush(t); /*printf("\nPushing Sub: %d",t);*/ptr++;
		break;
		case '^':t = exponent(); ipush(t); /*printf("\nPushing Exp: %d",t);*/ptr++;
		break;
		default : goto do_again;
		break;
	}

	for(int i = 0; i > 0; i++)
	{
		if (i == ((val.c)+1))
		{
			break;
		}
		//printf("\n hey%d->",val.data[i]);
	}
	goto do_again;
}
int multiply()
{
	int b = ipop();
	int a = ipop();
	return(a*b);
}
int divide()
{
	int b = ipop();
	int a = ipop();
	return((int)(a/b));
}
int add()
{
	int b = ipop();
	int a = ipop();
	return(a+b);
}
int subtract()
{
	int b = ipop();
	int a = ipop();
	return(a-b);
}
int exponent()
{
	int b = ipop();
	int a = ipop();
	return(int)(pow((double)(a),(double)(b)));
}
