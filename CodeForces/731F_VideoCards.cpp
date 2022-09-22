#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[200100];
int cnt[400100];
bool mark[200100];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		cnt[tbl[i]]++;
	}
	int cur=0;
	for (int i=1;i<=200000;i++) {
		cur+=cnt[i];
		cnt[i]=cur;
		//printf("%d\n",cnt[i]);
	}
	int now;
	long long ans;
	long long maxx=0;
	////printf("Yay\n");
	for (int i=0;i<n;i++) {
		if (mark[tbl[i]]) continue;
		now = tbl[i];
		mark[tbl[i]]=true;
		ans = 0;
		for (int j=now;j<=200000;j+=now) {
			ans+=(long long)(cnt[min(j+now-1,200000)]-cnt[j-1])*j;
			//printf("--%d %d %d\n",j,cnt[j+now-1],cnt[j-1]);
		}
		//printf("%d %I64d\n",now,ans);
		maxx=max(maxx,ans);
	}
	printf("%I64d\n",maxx);
	return 0;
}
