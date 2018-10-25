#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void print(int *arr, int a,  int b){
	for(int i = a; i<(b+1);i++){
		printf("%d-",arr[i]);
	}
	printf("\n");
}

void bubble(int *arr, int n){
	for(int i=n-1;i!=0;i--){
		for(int j=1;j<=i;j++){
			if(arr[j]<arr[j-1]){
				int t = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = t;
			}
		}
	}
}

void select(int *arr, int n){
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			if(arr[j]<arr[i]){
				int t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}
}

void insert(int *arr, int n){
	for(int i=0;i<n;i++){
		for(int j=i;j!=0;j--){
			if(arr[j]<arr[j-1]){
				int t = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = t;
			}
		}
	}
}

void main(){
	int arr1[10] = {10,9,56,23,79,3,1,6,2,5};
	int arr2[10] = {10,9,56,23,79,3,1,6,2,5};
	int arr3[10] = {10,9,56,23,79,3,1,6,2,5};
	print(arr1,0,9);
	print(arr2,0,9);
	print(arr3,0,9);
	bubble(arr1,10);
	select(arr2,10);
	insert(arr3,10);
	print(arr1,0,9);
	print(arr2,0,9);
	print(arr3,0,9);
}