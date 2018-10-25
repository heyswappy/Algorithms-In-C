#include<stdio.h>
#include<stdlib.h>

int *counting_sort(int *arr, int n, int k)
{
	int *ind = (int*)calloc(sizeof(int),k+1);
	int *ans = (int*)calloc(sizeof(int),n);

	for(int i = 0; i <= k; i++)
	{
		ind[i] = 0;
	}
	// count the number of occurences of arr[i]
	for(int i = 0; i < n; i++)
	{
		ind[arr[i]]++;
	}

	for(int i = 1; i <= k; i++)
	{
		ind[i] = ind[i]+ind[i-1];
	}

	for(int i = 0; i < n; i++)
	{
		ans[ind[arr[i]]-1] = arr[i];
		ind[arr[i]]--;
	}
	free(ind);
	return ans;
}

void main(){
	// do something
}