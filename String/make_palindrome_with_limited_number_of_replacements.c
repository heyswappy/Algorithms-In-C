#include<stdio.h>
#include<stdlib.h>

/*You are given a string representation of a number and maximum number of changes
you can make. Alter the string, one digit at a time, to create the largest palindromic string
of digits which is possible given the limit of number of changes.*/

int palindrome(int *arr, int n, int mx){
	int i,j,step;
	int mem[n];
	i = 0;
	j = n-1;
	step = 0;
	while(i<j && mx){
		if(arr[i]!=arr[j]){
			if(arr[i] > arr[j]){
				arr[j] = arr[i];
				mem[j] = 1;
			}
			else{
				arr[i] = arr[j];
				mem[i] = 1;
			}
			step++; mx--;
		}
		i++;j--;
	}
	i = 0;
	j = n-1;
	while(i<=j && mx){
		if(!mem[i] && !mem[j] && (mx>=2)){
			if(arr[i]!=9){
				arr[i]=9;
				arr[j]=9;
				mx -= 2;
				step += 2;
			}
			else{
				continue;
			}
		}
		else if(!mem[i] || !mem[j]){
			if(arr[i]!=9){
				arr[j] = 9;
				arr[i] = 9;
				mx--;
				step++;
			}
		}
		else if(i==j){
			if(arr[i]!=9){
				arr[i] = 9;
				mx--;
				step++;
			}
		}
		else{

		}
		i++;
		j--;
	}
	return step;
}

void main(){
	int i,n,m;
	printf("Enter the lenght and maximum number of changes: ");
	scanf("%d %d",&n,&m);
	int arr[n];
	printf("Enter the sequence: ");
	for(i=0;i<n;i++){
		scanf("%d",arr+i);
	}
	palindrome(arr,n,m);
	for(i=0;i<n;i++){
		printf("%2d",arr[i]);
	}
	return;
}
