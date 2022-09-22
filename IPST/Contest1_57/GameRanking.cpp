#include <cstdio>
#include <cassert>
#include <queue>
#include <vector>

using namespace std;

vector<int> pth[5010];
vector<int> pth2[5010];
int in[5010];

int grp[5010];
int grpSz[5010];
int d[5010];
int low[5010];

int time;
bool inStk[5010];
vector<int> stk;

int grpCnt;

int ans[5010];

//bool visit[5010];
int depth[5010];

int dep(int idx) {
	if (depth[idx]) return depth[idx];
	depth[idx]=0;
	for (auto &j:pth2[idx]) {
		depth[idx]=max(depth[idx],dep(j));
	}
	depth[idx]++;
	ans[depth[idx]]+=grpSz[idx];
	return depth[idx];
}

void dfs(int idx) {
	//printf("c %d\n",idx);
	d[idx]=low[idx]=++time;
	stk.push_back(idx);
	inStk[idx]=true;

	for (auto &a:pth[idx]) {
		if (!d[a]) {
			//printf("++ %d\n",a);
			dfs(a);
			low[idx]=min(low[idx],low[a]);
		} else if (inStk[a]) {
			low[idx]=min(low[idx],d[a]);
		}
	}
	
	if (low[idx]==d[idx]) {
		int now;
		grpCnt++;
		//printf("--> %d\n",grpCnt);
		while (stk.back()!=idx) {
			now=stk.back();
			stk.pop_back();
			inStk[now]=false;
			grp[now]=grpCnt;
			grpSz[grpCnt]++;
			//printf("%d ",now);
		}
		inStk[stk.back()]=false;
		grp[stk.back()]=grpCnt;
		grpSz[grpCnt]++;
		//printf("%d\n",stk.back());
		stk.pop_back();	
	}
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	int a,b;
	for (int i=0;i<k;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
	}
	for (int i=0;i<n;i++) {
		if (d[i]) continue;
		dfs(i);
	}
	for (int i=0;i<n;i++) {
		for (auto &j:pth[i]) {
			if (grp[i]==grp[j]) continue;
			pth2[grp[j]].push_back(grp[i]);
			//in[grp[j]]++;
		}
	}
	queue<pair<int,int>> q;
	for (int i=1;i<=grpCnt;i++) {
		if (depth[i]) continue;
		dep(i);
	}
	for (int i=1;ans[i]!=0;i++) {
		printf("%d ",ans[i]);
	}
	printf("\n");
	return 0;
}
