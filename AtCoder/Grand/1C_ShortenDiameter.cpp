#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> pth[2010];

int dfs2(int idx,int par,int dep) {
	if (dep==0) return 0;
	int cnt=1;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par) continue;
		cnt+=dfs2(pth[idx][i],idx,dep-1);
	}
	return cnt;
}

int n,k;
int dfs(int idx,int par) {
	int ans=0;
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (pth[idx][i]==par) continue;
		ans=max(ans,dfs2(pth[idx][i],idx,k));		
	}
	return ans+1;
}

vector<pair<int,int>> edge;

int main () {
	scanf("%d%d",&n,&k);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
		edge.push_back({a,b});
	}
	int mx=0;
	if (k%2==0) {
		for (int i=1;i<=n;i++) {
			mx=max(mx,dfs2(i,0,k/2+1));
		}
	} else {
		for (int i=0;i<(int)edge.size();i++) {
			mx=max(mx,dfs2(edge[i].first,edge[i].second,k/2+1)+dfs2(edge[i].second,edge[i].first,k/2+1));
		}
	}
	printf("%d\n",n-mx);
	return 0;
}
