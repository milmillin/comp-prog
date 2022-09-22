#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int par[100100];
int cnt[100100];
vector<int> pth[100100];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	cnt[1]=1;
	for (int i=2;i<=n;i++) {
		scanf("%d",&par[i]);
		pth[par[i]].push_back(i);
		cnt[i]++;
		int cur=par[i];
		while (cur) {
			cnt[cur]=1;
			for (auto jj:pth[cur]) {
				cnt[cur]+=cnt[jj];
			}
			if (cnt[cur]==k) cnt[cur]=0;
			cur=par[cur];
		}
		//for (int j=1;j<=n;j++) {
			//printf("%d ",cnt[j]);
		//}
		//printf("\n");
		printf("%s\n",cnt[1]==0?"YES":"NO");
	}	
	return 0;
}
