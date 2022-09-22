#include <cstdio>
#include <cstring>

using namespace std;

int ans[4][6]={{4,5,6,3,2,1},{11,12,13,10,9,8},{4,5,6,3,2,1},{11,12,13,10,9,8}};

int main () {
	char x[100];
	scanf("%s",x);
	int len=strlen(x);
	char col=x[len-1];
	x[len-1]=0;
	long long row;
	sscanf(x,"%I64d",&row);
	row--;
	long long mul=row/4;
	long long mod=row%4;
	printf("%I64d\n",mul*16+ans[mod][col-'a']);
	return 0;
}
