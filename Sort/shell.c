#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void print(int *arr, int a,  int b){
	for(int i = a; i<(b+1);i++){
		printf("%d-",arr[i]);
	}
	printf("\n");
}

void shell(int *arr, int n){
	int i,j,k,temp;
	int gap = 1;
	while(gap<n){
		gap = gap*2;
	}
	do{
		gap = gap/2;
		for(i=0;i<gap;i++){
			for(j=i+gap;j<n;j+=gap){
				for(k=j;k>=gap;k-=gap){
					if(arr[k-gap]>arr[k]){
						// swap them
						temp = arr[k];
						arr[k] = arr[k-gap];
						arr[k-gap] = temp;
					}
				}
			}
		}
	}while(gap!=1);
}

int main(){
	int arr[10] = {10,9,56,23,798,0,1,6,2,5};
	for(int i = 0;i<10;i++){
		printf("%d->",arr[i]);
	}
	printf("\n");
	shell(arr,10);
	for(int i = 0;i<10;i++){
		printf("%d<",arr[i]);
	}
	return 1;
}
