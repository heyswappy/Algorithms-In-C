#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define and &&
#define or ||
#define not !


int knightsTourCore(int n, int **board, int x, int y, int rem){
	int i, j, stat;
	stat = 0;
	// if no remaining box to travel puzzle complete
	if(rem==0) return 1;
	/* since later in this function we are automating the moves without any bounding function
	to check if they are valid positions we do that here*/
	if(x<0 or x>=n or y<0 or y>=n) return 0;
	// check if the box is visited
	if(board[y][x]!=0) return 0;

	// mark current box as visited
	board[y][x] = rem;
	rem -= 1;

	// automate the moves with loops
	for(i=x-2; i<x+3; i+=4){
		for(j=y-1; j<y+2; j+=2){
			stat = knightsTourCore(n, board, i, j, rem);
			if(stat==1) return 1;
		}
	}
	for(i=y-2; i<y+3; i+=4){
		for(j=x-1; j<x+2; j+=2){
			stat = knightsTourCore(n, board, j, i, rem);
			if(stat==1) return 1;
		}
	}

	// correct path not found so revert back the changes
	board[y][x] = 0;
	rem += 1;
	return 0;
}

int knightsTour(int n, int x, int y){
	int **board = (int**)calloc(sizeof(int*),n);
	int i;
	for(i=0; i<n; i++){
		board[i] = (int*)calloc(sizeof(int),n);
	}
	int stat = knightsTourCore(n, board, x, y, n*n);
	if(stat == 1){
		show(board, n);
		return 1;
	}
	return 0;
}

void show(int **board, int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void main(){
	int n;
	printf("ENTER THE DIMENSION: ");
	scanf("%d",&n);
	printf("\n");
	int s = knightsTour(n,0,0);
	if(s==1){
        printf("FOUND");
	}
	else{
        printf("NOT FOUND");
	}
	return;
}
