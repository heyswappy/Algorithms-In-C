#include<stdio.h>
#include<stdlib.h>

void prefix(char *s, int *table, int n){
	int i,j;
	i=1;
	j=0;
	while(i<n){
		if(s[i]==s[j]){
			table[i] = j+1;
			i++;
			j++;
		}
		else if(j>0){
			j = table[j-1];
		}
		else{
			table[i] = 0;
			i++;
		}
	}
	return;
}

int kmp(char *p, char *s, int n, int m){
		int i, j, table[n];
		prefix(p, table, n);
		i=0;
		j=0;
		while(i<m){
			if(p[j] == s[i]){
				if(j==n-1){
					return i-j;
				}
				else{
					i++;
					j++;
				}
			}
			else if(j>0){
				j = table[j-1];
			}
			else{
				i++;
			}
		}
		return -1;
}

void main(){
	int i, n, m;
	printf("Enter the lenght of pattern and string: ");
	scanf("%d %d",&n, &m);
	char p[n+1];
	char t[m+1];
	printf("Enter the pattern: ");
	scanf("%s",p);
	printf("Enter the string: ");
	scanf("%s",t);
	int ind = kmp(p, t, n, m);
	printf("Answer is at index: %d\n-->",ind);
	for(i=ind;i<ind+n;i++){
		printf("%c",t[i]);
	}
}
