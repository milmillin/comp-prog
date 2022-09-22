#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[5100];

long long ans;

int n;

long long mark[5010][5];
int cur[5010];

void dfs(int idx,int p,int d) {
	cur[d]++;
	for (auto i:pth[idx]) {
		if (i==p) continue;
		dfs(i,idx,d+1);
	}
}


int main () {
	scanf("%d", &n);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	for (int i=1;i<=n;i++) {
		//printf("-%d\n",i);
		memset(mark,0,sizeof(mark));
		for (auto j:pth[i]) {
			memset(cur,0,sizeof(cur));
			//printf("--%d\n",j);
			dfs(j,i,1);
			for (int k=1;k<n;k++) {
				//printf("%d ",cur[k]);
				mark[k][3]+=mark[k][2]*cur[k];
				mark[k][2]+=mark[k][1]*cur[k];
				mark[k][1]+=cur[k];	
			}
			//printf("\n");
		}
		for (int j=1;j<n;j++) {
			ans+=mark[j][3];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
