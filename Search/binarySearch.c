#include<stdio.h>
#include<stdlib.h>

int binSearchRecursive(int *arr, int n, int start, int end){
	// n is the number to search and start and end are starting and ending indices
	int mid = (start + end) / 2;
	//printf("%d\n",arr[mid] );
	if(start>=end){
		// element not found
		return -1;
	}
	if(arr[mid] == n){
		return mid;
	}
	else{
		//printf("%d\n",arr[mid]);
		if(arr[mid] > n){
			return binSearchRecursive(arr,n,start,mid-1);
		}
		else{
			return binSearchRecursive(arr,n,mid+1,end);
		}
	}
}

int binSearchIter(int *arr, int n, int l){
	// n is the number to search and l is the lenght of array
	int start =  0;
	int end = l-1;
	int mid = (start+end)/2;
	while(start <= end){
		//printf("%d\n",arr[mid]);
		if(arr[mid] == n){
			return mid;
		}
		else if(arr[mid] > n){
			end = mid-1;
		}
		else{
			start = mid+1;
		}
		mid = (start+end)/2;
	}
	return -1;
}

void main(){
	// do something
	int arr[5] = {0,5,56,65,89};
	//int s = binSearchRecursive(arr,65,0,4);
	//int s = binSearchIter(arr,89,5);
	//printf("-->%d",s);
}
