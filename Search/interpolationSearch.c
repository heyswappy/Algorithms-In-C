#include<stdio.h>
#include<stdlib.h>

int interpolationSearch(int *arr, int n, int l){
	// l is the lenght of the array
	int low = 0;
	int high = l-1;
	int ind = low + ((n-arr[low])*(high-low))/(arr[high]-arr[low]) ;
	while(low<=high){
		if(arr[ind] == n){
			return ind;
		}
		else if(arr[ind] > n){
			high = ind-1;
			int n = low + ((n-arr[low])*(high-low))/(arr[high]-arr[low]);
			if(n == ind){
				ind--;
			}
			else{
				ind = n;
			}
		}
		else{
			low = ind+1;
			int n = low + ((n-arr[low])*(high-low))/(arr[high]-arr[low]);
			if(n == ind){
				ind++;
			}
			else{
				ind = n;
			}
		}
	}
	return -1;
}

void main(){
	// do something
	int arr[5] = {0,5,56,65,89};
	int s = interpolationSearch(arr,89,4);
	printf("-->%d",s);
}
