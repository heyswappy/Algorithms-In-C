#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

int lis(int *s1, int *s2, int l){
    int sol[3][l];
    int i,j,mx,mxi;
    for(i=0;i<l;i++){
        sol[0][i] = s1[i];
        sol[1][i] = 1;
        sol[2][i] = i;
    }
    for(i=1;i<l;i++){
        for(j=0;j<i;j++){
            if( (sol[0][j] < sol[0][i]) && (sol[1][i] < sol[1][j]+1) ){
                sol[1][i] = sol[1][j]+1;
                sol[2][i] = j;
            }
        }
    }
    mx = sol[1][0];
    mxi = 0;
    for(i=0;i<l;i++){
        if(sol[1][i] > mx){
            mx = sol[1][i];
            mxi = i;
        }
    }
    i = mxi;
    j = 0;
    while(i != sol[2][i]){
        s2[mx-j-1] = sol[0][i];
        i = sol[2][i];
        j++;
    }
    s2[mx-j-1] = sol[0][i];
    return mx;
}

void lis_recurse(int *s1, int *s2, int *s3, int i1, int i2, int *i3, int l){
    int i;
    if(i1 >= l) return;
    if((s1[i1] > s2[i2-1])||(i2==0)){
        s2[i2] = s1[i1];
        if(*i3 < i2){
            *i3 = i2;
            for(i=0;i<i2+1;i++){
                s3[i] = s2[i];
            }
        }
        lis_recurse(s1, s2, s3, i1+1, i2+1, i3, l);
    }
    lis_recurse(s1, s2, s3, i1+1, i2, i3, l);
    return;
}

void main(){
    int i,l;
    printf("Enter the lenght of the sequence: ");
    scanf("%d",&l);
    int s1[l+1];
    int s2[l+1];
    int s3[l+1];
    int s4[l+1];
    int i3 = 0;
    printf("Enter the sequence: ");
    for(i=0;i<l;i++){
        scanf("%d",s1+i);
    }
    int ans = lis(s1,s4,l);
    lis_recurse(s1, s2, s3, 0, 0, &i3, l);

    printf("DP answer is: %d\n",i3+1);
    for(i=0;i<ans;i++){
        printf("%d ",s4[i]);
    }
    printf("\n");
    printf("Recursive answer is: %d\n",i3+1);
    for(i=0;i<i3+1;i++){
        printf("%d ",s3[i]);
    }
}
