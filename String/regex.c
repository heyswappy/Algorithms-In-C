#include<stdio.h>
#include<stdlib.h>

int max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

void character(char *p, char *s, int m, int n){
	int i;
	if(m!=n) return;
	for(i=0;i<n;i++){
		if(p[i]==s[i] || p[i]=='?') continue;
		else{
			printf("Match failed!\n");
			return;
		}
	}
	printf("Match success!\n");
	return;
}

void sequence(char *p, char *s, int m, int n){
	m++;n++;
	int sol[n][m];
	int i, j;
	for(i=0;i<m;i++){
		sol[0][i] = 0;
	}
	for(i=0;i<n;i++){
		sol[i][0] = 0;
	}
	sol[0][0] = 1;

	for(i=1;i<n;i++){
		for(j=1;j<m;j++){
			if(s[i-1] == p[j-1] && sol[i-1][j-1]){
				// hit with previous match
				sol[i][j] = 1;
			}
			else if(p[j-1] == '*'){
				// wild card
				sol[i][j] = max(sol[i][j-1], sol[i-1][j]);
			}
			else{
				sol[i][j] = 0;
			}
		}
	}
	if(sol[n-1][m-1] == 1) printf("Match success\n");
	else printf("Match failed\n");
}

void main(){
	int m, n;
	char *p, *s;
	printf("Enter the lenght of pattern: ");
	scanf("%d",&m);
	printf("Enter the lenght of string: ");
	scanf("%d",&n);
	p = (char*)calloc(sizeof(char),m+1);
	s = (char*)calloc(sizeof(char),n+1);
	printf("Enter the pattern: ");
	scanf("%s",p);
	printf("Enter the string: ");
	scanf("%s",s);
	sequence(p, s, m, n);
	return;
}
