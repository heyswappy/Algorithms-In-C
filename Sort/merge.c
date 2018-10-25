#include<stdio.h>
#include<stdlib.h>
#include <conio.h>

void print(int *arr, int a,  int b){
	for(int i = a; i<(b+1);i++){
		printf("%d-",arr[i]);
	}
	printf("\n");
}

void merge(int *arr, int s, int m, int e){
	//printf("TO MERGE: \n");
	//print(arr,s,e);
	int l = e-s+1 ;
	int m1 = m;
	int m2 = m+1;
	int *t = (int*)calloc(sizeof(int),l);
	int i = s;
	int j = m2;
	int c = 0;
	while(i!=(m+1)&&j!=(e+1)&&(c!=l)){
		if(arr[i]<arr[j]){
			t[c] = arr[i];
			i++;
			c++;
		}
		if(arr[i]>=arr[j]){
			t[c] = arr[j];
			j++;
			c++;
		}
	}
	while(i!=(m+1)){
		t[c] = arr[i];
		i++;
		c++;
	}
	while(j!=(e+1)){
		t[c] = arr[j];
		j++;
		c++;
	}
	for( i=s, c=0; c<l;i++,c++){
		arr[i]=t[c];
	}
	free(t);
	return;
}


void mergeSort(int *arr, int s, int e){
	if((s==e)){ //||((s-e)==1)||((e-s)==1)){
		return;
	}
	int mid = (s+e)/2;
	//printf("SPLIT TO: ");
	//print(arr,s,mid);
	mergeSort(arr,s,mid);
	//printf("SPLIT TO: ");
	//print(arr,mid+1,e);
	mergeSort(arr,mid+1,e);
	merge(arr,s,mid,e);
	//printf("AFTER MERGING: ");
	//print(arr,s,e);
}

int main(){
	int arr[10] = {10,9,56,23,798,3,1,6,2,5};
	for(int i = 0;i<10;i++){
		printf("%d->",arr[i]);
	}
	printf("\n");
	mergeSort(arr,0,9);
	for(int i = 0;i<10;i++){
		printf("%d<",arr[i]);
	}
	return 1;
}
