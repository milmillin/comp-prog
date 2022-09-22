#include <cstdio>
#include <algorithm>

using namespace std;

int c[200];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	if (n>20) return 0;
	int e=1<<k;
	for (int i=0;i<e;i++) {
		scanf("%d",&c[i]);
	}
	int mask=e-1;
	int ee=1<<n;
	int mx=0;
	for (int i=0;i<ee;i++) {
		int sum=0;
		for (int j=0;j<n-k+1;j++) {
			sum+=c[((mask<<j)&i)>>j];
		}	
		mx=max(mx,sum);
	}
	printf("%d\n",mx);
	return 0;
}
