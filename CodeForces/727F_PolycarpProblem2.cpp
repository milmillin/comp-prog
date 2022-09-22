#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int tbl[1000];
long long mic[1000][1000];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	//memset(mic,127,sizeof(mic));
	for (int i=n-1;i>=0;i--) {
		mic[i][0]=max(0ll,mic[i+1][0]-tbl[i]);
		for (int j=1;j<=n;j++) {
			mic[i][j]=max(mic[i+1][j]-tbl[i],0ll);
			if (tbl[i]<0) mic[i][j]=min(mic[i][j],mic[i+1][j-1]);
		}
	}

	long long x;
	for (int i=0;i<k;i++) {
		scanf("%I64d",&x);
		for (int j=0;j<=n;j++) {
			if (mic[0][j]<=x) {
				printf("%d\n",j);
				break;
			}
		}
	}
	return 0;
}
