#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}

void retrace(char *s1, char *s3, int a, int b, int **sol){
	int i,j;
	i = a-1;
	j = b-1;
	while(sol[j][i] != 0){
		if(sol[j][i]-1 == sol[j-1][i-1]){
			// it was a hit
			s3[sol[j][i]-1] = s1[i-1];
			i--;
			j--;
		}
		else{
			if(sol[j][i] == sol[j][i-1]) i--;
			else j--;
		}
	}
	return;
}

void lcs(char *s1, char*s2, char *s4, int a, int b){
    a++; b++;
    int **sol;
    int i,j;
    sol = (int**)calloc(sizeof(int*),b);
    for(i=0;i<b;i++) sol[i] = (int*)calloc(sizeof(int),a);
    for(i=0;i<a;i++){
        sol[0][i] = 0;
    }
    for(j=0;j<b;j++){
        sol[j][0] = 0;
    }
    for(j=1; j<b; j++){
        for(i=1; i<a; i++){
            if(s1[i-1] == s2[j-1]){
                //hit condition
                sol[j][i] = sol[j-1][i-1]+1;
            }
            else{
                // miss condition
                sol[j][i] = max(sol[j][i-1], sol[j-1][i]);
            }
        }
    }
    int ans = sol[b-1][a-1];
    char s3[ans+1];
    s3[ans] = '\0';
    retrace(s1,s3,a,b,sol);
    strcpy(s4,s3);
    return;
}

void lcs_recurse(char *s1, char *s2, char*s3, char *s4, int i1, int i2, int i3, int l1, int l2){
    if(!((i1<l1)&&(i2<l2))) return;
    if(s1[i1]==s2[i2]){
        s3[i3] = s1[i1];
        if(i3+1 > strlen(s4)) strcpy(s4,s3);
        lcs_recurse(s1,s2,s3,s4,i1+1,i2+1,i3+1,l1,l2);
        s3[i3] = '\0';
        return;
    }
    lcs_recurse(s1,s2,s3,s4,i1+1,i2,i3,l1,l2);
    lcs_recurse(s1,s2,s3,s4,i1,i2+1,i3,l1,l2);
}

void main(){
    int l1, l2;
    printf("Enter the lenght of the two strings: ");
    scanf("%d %d",&l1, &l2);
    char s1[l1+1], s2[l2+1];
    int t = max(l1,l2);
    char s3[t+1];
    char s4[t+1];
    char s5[t+1];
    printf("Enter the first string: ");
    scanf("%s",s1);
    printf("Enter the second string: ");
    scanf("%s",s2);
    lcs(s1, s2, s5, l1, l2);
    lcs_recurse(s1,s2,s3,s4,0,0,0,l1,l2);
    printf("Answer due to recursion: %s\n",s5);
    printf("Answer due to DP: %s\n",s4);
}
