#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void quick(int *arr, int s, int e){
	if(s>=e){
		return;
	}
	int pivot = arr[s];
	int i,j;
	i=s+1;
	j=e;
	while(i<j){
		while(arr[i]<=pivot && i<=j){
			i++;
		}
		while(arr[j]>pivot && i<=j){
			j--;
		}
		if(i>=j){
			break;
		}
		// swap i,j
		int t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
		i++;
		j--;
	}
	// swap pivot
	arr[s] = arr[i-1];
	arr[i-1] = pivot;

	quick(arr,s,i-1);
	quick(arr,i,e);
}

int main(){
    int n;
    printf("Number of elements: ");
    scanf("%d",&n);
	int arr[n];
	for(int i = 0;i<n;i++){
		scanf("%d",arr+i);
	}
	for(int i = 0;i<n;i++){
		printf("%d->",arr[i]);
	}
	printf("\n");
	quick(arr,0,n-1);
	for(int i = 0;i<n;i++){
		printf("%d->",arr[i]);
	}
	return 1;
}
