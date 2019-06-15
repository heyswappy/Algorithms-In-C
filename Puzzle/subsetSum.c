#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define and &&
#define or ||
#define not !

int subsetSum(int *arr, int s, int e, int sum){
	int stat = 0;
	if(s>=e) return 0;
	if(sum==0) return 1;
	if(sum<0) return 0;
	// inlcude current element
	stat = subsetSum(arr, s+1, e, sum-arr[s]);
	if(stat == 1) return 1;
	// do not inlcude current element
	stat = subsetSum(arr, s+1, e, sum);
	if(stat == 1) return 1;
	return 0;
}

void main(){
	int i, n, s;
	printf("ENTER THE NUMBER OF INTEGERS: ");
	scanf("%d",&n);
	int arr[n];
	printf("ENTER THE SUM TO FIND: ");
	scanf("%d",&s);
	printf("ENTER THE NUMBERS: ");
	for(i=0;i<n;i++){
		scanf("%d",arr+i);
	}
	int stat = subsetSum(arr, 0, n, s);
	if(stat == 1){
		printf("FOUND SUM\n");
	}
	else{
		printf("SUM NOT FOUND\n");
	}
	return;
}
