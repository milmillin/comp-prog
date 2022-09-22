#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int len;

void rev(const char *a,char *ans,int n) {
	if (n==len) return;
	*ans=*a;
	rev(a+1,ans-1,n+1);
}

int main () {
	char x[2000],y[2000];
	scanf("%s",x);
	len=strlen(x);
	y[len]=0;
	rev(x,y+len-1,0);
	printf("%s\n",y);
	return 0;
}
