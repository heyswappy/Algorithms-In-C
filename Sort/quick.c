#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void quick(int *arr, int s, int e){
	if((s==e)||((s-e)==1)||((e-s)==1)){
		return;
	}
	int pivot = arr[s];
	int i,j;
	i=s+1;
	j=e;
	while(i<j){
		while(arr[i]<pivot){
			i++;
		}
		while(arr[j]>pivot){
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
	int arr[10] = {10,9,56,23,798,0,1,6,2,5};
	for(int i = 0;i<10;i++){
		printf("%d->",arr[i]);
	}
	printf("\n");
	quick(arr,0,9);
	for(int i = 0;i<10;i++){
		printf("%d<",arr[i]);
	}
	return 1;
}