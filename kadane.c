#include<stdio.h>

int kadane(int *a,int b);

void main()
{
	int n = 0; //size
	scanf("%d",&n);
	int arr[n];

	for (int i =0;i<n;i++)
	{
		scanf("%d",arr+i);
	}
	printf("%d",kadane(arr,n));
}

int kadane(int *arr, int n)
{
	int max_so_far = 0 ;
	int max_ending_here = 0 ;

	int j;
	int max_among_negative = *(arr);
	for(j =0; j<n;j++)
	{
		if (*(arr+j)>0)
		{
			//presence of even one one positive term would do the trick
			break ;
		}
		else
		{
			if (*(arr+j)>max_among_negative)
			{
				max_among_negative = *(arr+j) ;
			}
		}
	}

	// if array all negative then answer is the least negative number
	if (j == n)
	{
		return max_among_negative ;
	}

	for(int i = 0; i<n ; i++)
	{
		max_ending_here += *(arr+i) ;

		if (max_ending_here<=0)
		{
			max_ending_here = 0 ;
		}
		if(max_ending_here>max_so_far)
		{
			max_so_far = max_ending_here ;
		}
	}

	return max_so_far ;

}