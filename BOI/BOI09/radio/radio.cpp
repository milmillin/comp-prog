#include <cstdio>
#include <algorithm>

using namespace std;


char buf[1000100];

int f[1000100];

int main () {
	//freopen("radio9.in","r",stdin);
	int n;
	scanf("%d",&n);
	scanf("%s",buf);
	f[0]=-1;	
	int cur=-1;
	for (int i=1;i<n;i++) {
		while (cur>-1&&buf[cur+1]!=buf[i]) cur=f[cur];	
		if (buf[cur+1]==buf[i]) cur++;
		f[i]=cur;
	}

	cur=-1;
	for (int i=1;i<n;i++) {
		while (cur>-1&&buf[cur+1]!=buf[i]) cur=f[cur];
		//printf("\n");
		if (buf[cur+1]==buf[i]) cur++;
		if (i==n-1) {
			printf("%d\n",i-cur);
			return 0;
		}
		//printf("%d %dn",i,cur);
	}
	printf("1\n");
	return 0;
}
