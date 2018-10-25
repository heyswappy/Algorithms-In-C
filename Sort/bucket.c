#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int *bucket(int *arr, int n, int max){
	int bucketQuant = ceil(max/500);
	int *ans = (int*)calloc(sizeof(int),n);
	int **bucket = (int**)calloc(sizeof(int*),bucketQuant);
	for(int i=0;i<500;i++){
		bucket[i] = (int*)calloc(sieof(int),500);
	}
	int q,r;
	for(int i=0;i<n;i++){
		q = arr[i]/500;
		r = arr[i]%r;
		bucket[q][r]++;
	}
	for(int i=0;i<bucketQuant;i++){
		count()
	}
}

void main(){
	int arr[10] = {10,9,56,23,79,0,1,6,2,5};
	for(int i = 0;i<10;i++){
		printf("%d->",arr[i]);
	}
	printf("\n");
	int *ptr = count(arr,10,80);
	for(int i = 0;i<10;i++){
		printf("%d<",ptr[i]);
	}
}
