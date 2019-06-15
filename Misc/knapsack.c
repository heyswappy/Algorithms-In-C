#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define and &&
#define or ||
#define not !

int classic(int *wt, int *val, int size, int obj, int rem){
	// 0-1 knapsack classic problem wherin we fill the sack comletely
	int a, b;
	a = -1;
	if(rem==0 || obj>=size) return 0;
	// select current object
	if(rem>=wt[obj]){
		a = val[obj]+classic(wt, val, size, obj+1, rem-wt[obj]);
	}
	// reject current object
	b = classic(wt, val, size, obj+1, rem);
	if(a>b) return a;
	return b;
}

int integer(int *wt, int *val, int size, int rem){
	// integer knapsack problem wherin we have infinite items of each type
	int a, b, i, t;
	if(rem<=0) return 0;
	b = -1;
	for(i=0; i<size; i++){
            if(rem<wt[i]){
                continue;
            }
            t = val[i]+integer(wt, val, size, rem-wt[i]);
            if(t>b) b=t;
	}
	a = integer(wt, val, size, rem-1);
	if(a>b) return a;
	return b;
}

int fraction(){
    // later
}


void main(){
	int i, n, c;
	printf("ENTER THE CAPACITY OF SACK: ");
	scanf("%d",&c);
	printf("ENTER THE NUMBER OF ITEMS: ");
	scanf("%d",&n);
	int val[n];
	int wt[n];
	printf("ENTER THE VALUES: ");
	for(i=0; i<n; i++){
		scanf("%d",val+i);
	}
	printf("ENTER THE WEIGHTS: ");
	for(i=0; i<n; i++){
		scanf("%d",wt+i);
	}
	int ans = integer(wt, val, n, c);
	printf("ANSWER IS: %d\n",ans);
	return;
}
