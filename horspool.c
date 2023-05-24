#include<stdio.h>
#include<string.h>

#define MAX 500


int t[MAX];
void shifttable(char p[]) {
	int i,j,m;
	m=strlen(p);
	for (i=0;i<MAX;i++)
	  t[i]=m;
	for (j=0;j<m-1;j++)
	  t[p[j]]=m-1-j;
}
int horspool(char src[],char p[]) {
	int i,j,k,m,n;
	n=strlen(src);
	m=strlen(p);
	i=m-1;
    int comp=0;
	while(i<n) {
		k=0;
		while((k<m)&&(++comp && p[m-1-k]==src[i-k]))
            
		   k++;
		if(k==m)
        {
            printf("\ncomp %d\n",comp);
		   return(i-m+1);
        }
             else
		   i+=t[src[i]];
	}
    printf("\nNumber of Comparissons %d\n",comp);
	return -1;
}
void main() {
	char p[25]="10000";
    char src[1001]="00000000001";

	int pos;

	
	shifttable(p);
	pos=horspool(src,p);
	if(pos>=0)
	  printf("\n The desired pattern was found starting from position %d",pos+1); else
	  printf("\n The pattern was not found in the given text\n");

}