#include <cstdio>
#include <algorithm>

using namespace std;

int a[100100];
int b[100100];

int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	long long ans=0;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&a[i],&b[i]);
		if ((a[i]|k)<=k) ans+=b[i];
	}
	for (int j=30;j>=0;j--) {
		long long now=0;
		if ((k&(1<<j))==0) continue;
		int w=k^(1<<j);
		w|=((1<<j)-1);
		for (int i=0;i<n;i++) {
			if ((a[i]|w)<=w) now+=b[i];
		}	
		ans=max(ans,now);
	}
	printf("%lld\n",ans);
	return 0;
}
