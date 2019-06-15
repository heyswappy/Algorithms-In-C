#include<stdio.h>
#include<stdlib.h>

int min(int a, int b){
    if(a>b){
        return b;
    }
    return a;
}

void convert(char *p, char *s, int m, int n){
	m++;n++;
	int sol[m][n];
	int i, j;
	for(i=0;i<n;i++){
		sol[0][i] = i;
	}
	for(i=0;i<m;i++){
		sol[i][0] = i;
	}
	sol[0][0] = 0;

	for(i=1;i<m;i++){
		for(j=1;j<n;j++){
			if(s[j-1] == p[i-1]){
				// hit
				sol[i][j] = sol[i-1][j-1];
			}
			else{
				// miss
				sol[i][j] = min(sol[i-1][j-1], min(sol[i][j-1], sol[i-1][j]))+1;
			}
		}
	}
	printf("Steps needed: %d",sol[m-1][n-1]);
}

void main(){
	int m, n;
	char *p, *s;
	printf("Enter the lenght of source string: ");
	scanf("%d",&m);
	printf("Enter the lenght of destination string: ");
	scanf("%d",&n);
	p = (char*)calloc(sizeof(char),m+1);
	s = (char*)calloc(sizeof(char),n+1);
	printf("Enter the source string: ");
	scanf("%s",p);
	printf("Enter the destination string: ");
	scanf("%s",s);
	convert(p, s, m, n);
	return;
}
