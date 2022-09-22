#include <cstdio>
#include <algorithm>

using namespace std;

int cnt[2000010];
int x[1010],y[1010];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x[i],&y[i]);
	}
	int ans=0;
	int a,b;
	int minn;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		minn=2e9;
		for (int j=0;j<n;j++) {
			minn=min(minn,abs(x[j]-a)+abs(y[j]-b));
		}
		cnt[minn]++;
		ans=max(ans,cnt[minn]);
	}
	printf("%d\n",ans);
	return 0;
}
