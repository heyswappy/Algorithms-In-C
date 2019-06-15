#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int queenStraight(int x, int y, int **board, int n){
    // x and y are the coordinates of the current piece
    // n is the size of board
    //printf("IN QUEENSTRAIGHT %d %d\n",x,y);
    // check the ith column by fixing y
    for(int i = 0; i<n; i++){
        if(i==x){
        continue;
        }
        if(board[y][i]>0){
            return 1;
        }
    }
    //printf("FIRST TIER COMPLETE IN QUEENSTRAIGHT\n");
    // check the ith row by fixing x
    for(int i = 0; i<n; i++){
        if(i==y){
        continue;
        }
        if(board[i][x]>0){
            return 1;
        }
    }
    //printf("SECOND TIER COMPLETE IN QUEENSTRAIGHT\n");
    return 0;
}

int queenDiagnol(int x, int y, int **board, int n){
    // x and y are the coordinates of the current piece
    // n is the size of board
    int tx, ty;
    //printf("IN QUEENDIAGNOL\n");
    tx = x-1;
    ty = y-1;
    while(tx>=0&&ty>=0){
        if(board[ty][tx]>0){
            return 1;
        }
        tx -=1;
        ty -=1;
    }
    //printf("FIRST TIER COMPLETE IN QUEENDIAGNOL\n");
    tx = x+1;
    ty = y+1;
    while(tx<n&&ty<n){
        if(board[ty][tx]>0){
            return 1;
        }
        tx +=1;
        ty +=1;
    }
    //printf("SECOND TIER COMPLETE IN QUEENDIAGNOL\n");
    tx = x-1;
    ty = y+1;
    while(tx>=n&&ty<n){
        if(board[ty][tx]>0){
            return 1;
        }
        tx -=1;
        ty +=1;
    }
    //printf("THIRD TIER COMPLETE IN QUEENDIAGNOL\n");
    tx = x+1;
    ty = y-1;
    while(tx<n&&ty>=0){
        if(board[ty][tx]>0){
            return 1;
        }
        tx +=1;
        ty -=1;
    }
    //printf("FOURTH TIER COMPLETE IN QUEENDIAGNOL\n");
    return 0;
}

int queenMate(int x, int y, int **board, int n){
    // x and y are the coordinates of the current piece
    // n is the size of board
    //printf("QUEENMATE\n");
    if(queenStraight(x, y, board, n) || queenDiagnol(x, y, board,n)){
        return 1;
    }
    //printf("QUEENMATE DONE\n");
    return 0;
}

int mQueen(int pos, int **board, int m, int n){
    //printf("\n\n\n");
    //show(board,n);
    //getch();
    int x = pos%n;
    int y = pos/n;
    int stat = -1; // a zero flag always indicates that the current positon of queen is not right

    if(!m){
        // all queens placed
        // printf("ALL PLACED\n");
        return 1;
    }
    if(pos>=(n*n)){
        return 0;
    }

    while(pos<(n*n)){
        if(!queenMate(x, y, board, n)){
            board[y][x] = m;
            stat = mQueen(pos+1, board, m-1, n);
        }
        if(stat==0){
            board[y][x] = 0;
        }
        else if(stat==1){
            return 1;
        }
        pos++;
    }

    return 0;
}

int** concierge(int n){
    int **ptr = (int**)calloc(sizeof(int*),n);
    for(int i=0; i<n; i++){
        ptr[i] = (int*)calloc(sizeof(int),n);
    }
    return ptr;
}

void show(int **arr, int n){
    for(int i=n-1; i>=0; i--){
        for(int j = 0; j<n; j++){
            printf("%2d ",arr[i][j]);
        }
        printf("\n");
    }
    return;
}

void main(){
    int n,m,ans;
    printf("Enter the number of rows: ");
    scanf("%d",&n);
    printf("Enter the number of queens: ");
    scanf("%d",&m);
    int **board = concierge(n);
    
    if(m>n){
        ans = 0;
    }
    else{
        ans = mQueen(0,board,m,n);
    }
    printf("\n\n\n");
    if(!ans){
        printf("NOT POSSIBLE");
    }
    else{
            show(board,n);
    }
}
