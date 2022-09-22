#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

long long  cost[200];
long long mic[100100][200];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	int e=1<<k;
	for (int i=0;i<e;i++) {
		scanf("%lld",&cost[i]);
	}
	int mask=1<<(k-1);
	mask-=1;
	int mfrn=mask<<1;
	//mfrn^=1;
	

	for (int i=k-1;i<n;i++) {
		for (int j=0;j<e;j++) {
			mic[i][(mfrn&j)>>1]=max(mic[i][(mfrn&j)>>1],mic[i-1][mask&j]+cost[j]);
		}
	}
	long long mx=0;
	for (int i=0;i<e;i++) {
		mx=max(mic[n-1][i],mx);	
	}
	printf("%lld\n",mx);
	return 0;
}
