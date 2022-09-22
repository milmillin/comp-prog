#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int tbl[10000];
vector<int> pth[10000];
bool visit[10000];
int ans=2e9;
int k;

void dfs(int idx,int val,int dep) {
	visit[idx]=true;
	if (val+tbl[idx]>=k) {
		if (dep) ans=min(ans,dep);
	}
	for (int i=0;i<(int)pth[idx].size();i++) {
		if (visit[pth[idx][i]]) continue;
		dfs(pth[idx][i],val+tbl[idx],dep+1);
	}
}

int main () {
	int n;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	for (int i=0;i<n;i++) {
		memset(visit,0,sizeof(visit));
		dfs(i,0,0);
	}
	
	printf("%d\n",(ans==2e9||ans==0)?-1:ans);
	return 0;
}
