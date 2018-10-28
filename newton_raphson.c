#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#define NEWLINE printf("\n") ;
#define AND &&
#define OR ||

void differential (int *a, int *b) ;

float _function (int *a, int *b, float c) ;

float _derivative (int *a, int *b, float c) ;

float _positive(int *a, int *b, float c) ;

float _negative(int *a, int *b, float c) ;

struct function
{
	int power[11] ;
	int coeff[11] ;
} ;
struct derivative
{
	int power[11] ;
	int coeff[11] ;
} ;
void main ()
{
	int i , degree = 0 ;
	struct function fun ;
	struct derivative diff ;
	// initialisation of fun structure variable
	for(i=0;i<11;i++)
	{
		fun.power[i] = i ;
		fun.coeff[i] = 0 ;
	}
	// initialisation of fun derivative variable
	for(i=0;i<11;i++)
	{
		diff.power[i] = i ;
		diff.coeff[i] = 0 ;
	}
	printf("Input the degree of polynomial from 1 to 10: ") ;
	scanf("%d",&degree) ;
	NEWLINE
	// to check the limit of degree and then add one to it to use in loops
	if ((degree<1)OR(degree>10))
	{
		printf("You entered wrong degree") ;
		NEWLINE
		printf("PROGRAM TERMINATED") ;
		NEWLINE
		exit(0) ;
	}
	else
	{
			++degree ;
	}
	// input the coefficients
	for(i=0;i<degree;i++)
	{
		printf("The coefficient of power %d is : ",i) ;
		scanf("%d",&fun.coeff[i]) ;
		NEWLINE
	}
	
	// the differential function saves new coefficients of the derivativee in the structure variable diff
	differential(&(fun.coeff[0]),&(diff.coeff[0])) ;

	float x = 1 , x_n ;
	
	while( /*(_function(&(fun.coeff[0]),&(diff.coeff[0]),x) != 0)
	OR*/
	(_function(&(fun.coeff[0]),&(diff.coeff[0]),x) > (0.001))
	OR
	(_function(&(fun.coeff[0]),&(diff.coeff[0]),x) < (-0.001)) )
	{
		x_n = x - ( _function(&(fun.coeff[0]),&(diff.coeff[0]),x) / _derivative(&(fun.coeff[0]),&(diff.coeff[0]),x) ) ;
		x = x_n ;
	}
	
	printf("%f",x) ;
}

// the differential function saves new coefficients of the derivativee in the structure variable diff
void differential (int *fun_coeff, int *der_coeff)
{
	int i ;

	for(i=0;i<10;i++)
	{
		*(der_coeff+i) = (*(fun_coeff+i+1))*(i+1) ;
	}
}

float _function (int *fun_coeff, int *der_coeff, float x)
{
	int i ;
	
	float sum = 0 ;

	for(i=0;i<11;i++)
	{
		sum = sum + ((*(fun_coeff+i))*(pow(x,i))) ;
	}
	
	return sum ;
}
// _derivative takes an x and returns f'(x)
float _derivative(int *fun_coeff, int *der_coeff, float x)
{
	int i ;
	
	float sum = 0 ;

	for(i=0;i<11;i++)
	{
		sum = sum + ((*(der_coeff+i))*(pow(x,i))) ;
	}
	
	return sum ;
}