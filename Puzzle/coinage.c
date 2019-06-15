#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define and &&
#define or ||
#define not !

int coinage(int *arr, int size, int cap){
	int a, i, t;
	if(cap==0) return 0;
    a = -cap;
    for(i=0;i<size;i++){
    	if(cap < arr[i]) continue;
    	t = coinage(arr, size, cap-arr[i]);
    	if(-a > -t) a = t;
    }
    return -1+a;
}

int coinageDp(int *arr, int size, int cap){
    int sol[cap+1];
    int a,i,j;
    for(i=0;i<cap+1;i++) sol[i]=-1;
    for(i=0;i<cap+1;i++){
        a = -1;
        for(j=0;j<size;j++){
            if(i-arr[j] > 0 && sol[i-arr[j]] != -1){
                    a = 1 + sol[i-arr[j]];
            }
            else if(i-arr[j] == 0){
                a = 1;
            }
            else{
                a = -1;
            }
            if(sol[i]==-1) sol[i] = a;
            else if(a==-1){

            }
            else{
                sol[i] = (sol[i]>a) ? a : sol[i];
            }
        }
    }
    for(i=0;i<cap+1;i++) printf("%d ",sol[i]);
    return sol[cap];
}

void main(){
	int i, n, amt;
	printf("ENTER THE NUMBER OF DENOMINATIONS: ");
	scanf("%d",&n);
	int arr[n];
	printf("ENTER THE DENOMINATIONS: ");
	for(i=0; i<n; i++){
		scanf("%d",arr+i);
		arr[i] = arr[i];
	}
	printf("ENTER THE AMOUNT: ");
	scanf("%d",&amt);
	int ans = coinageDp(arr, n, amt);
	printf("\nANSWER IS: %d",ans);
	return;
}
