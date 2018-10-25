#include<stdio.h>
#include<Stdlib.h>
#include<conio.h>
#include<math.h>

void show(int *a, int b, int c);

void countingSort(int *arr, int n, int exp);


void main()
{
	int t[8] = {123,456,789,741,852,963,753,951};
	countingSort(t,8,1);
	show(t,0,7);
}

void show(int *arr, int a, int b)
{
	for(int i=a;i<=b;i++)
	{
		printf("<%d",arr[i]);
	}
	printf("\n\n");
}

void countingSort(int *arr, int n, int exp)
{
	// k = 9 by default
	// exp is the decimal over which sorting is one
	int *count = (int*)calloc(sizeof(int),10);
	int *ans = (int*)calloc(sizeof(int),n);
	int digit = pow(10,exp);
	int mem;
	// initialize
	for(int i = 0; i < 10; i++)
	{
		count[i] = 0;
	}
	show(count,0,9);
	for(int i=0; i<n; i++)
	{
		printf("->%d\n",arr[i]-(((int)(arr[i]/digit))*digit));
		count[arr[i]-(((int)(arr[i]/digit))*digit)] += 1;
	}

	for(int i = 1; i<10; i++)
	{
		arr[i] = arr[i]+arr[i-1];
	}

	for(int i = 0; i<n; i++)
	{
		--count[arr[i]-(((int)(arr[i]/digit))*digit)];
		ans[count[arr[i]-(((int)(arr[i]/digit))*digit)]] = arr[i];
	}
	show(count,0,9);
	show(ans,0,n-1);
	for(int i = 0; i<n; i++)
	{
		arr[i] = ans[i];
	}
	free(count);
	free(ans);
	return;
}