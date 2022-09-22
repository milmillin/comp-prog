#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> pth[100100];


long long ans=0;
int n;
int sub[100100];
bool visit[100100];

void dfs(int x,int p) {
	visit[x]=true;
	n++;
	sub[x]=1;
	for (auto i:pth[x]) {
		if (i==p) continue;
		dfs(i,x);
		sub[x]+=sub[i];
	}	
}

void dfs2(int x,int p) {
	int tot=0;
	for (auto i:pth[x]) {
		if (i==p) continue;
		dfs2(i,x);
		tot+=sub[i];
	}
	int hi=n-sub[x];
	tot+=hi;
	for (auto i:pth[x]) {
		if (i==p) continue;
		ans+=(long long)(sub[i])*(tot-sub[i]);
	}
	ans+=(long long)hi*(tot-hi);
}

int main () {
	int m;
	scanf("%d%d",&n,&m);
	assert(m<=n-1);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	int nn=n;
	for (int i=1;i<=nn;i++) {
		if (visit[i]) continue;
		n=0;
		dfs(i,i);
		dfs2(i,i);
	}
	printf("%lld\n",ans);
	return 0;
}
