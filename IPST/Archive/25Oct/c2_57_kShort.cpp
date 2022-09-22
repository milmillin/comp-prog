#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

struct edge {
	int idx,wgt;
};

struct ei {
	int idx,wgt,lev;
};

bool operator< (const ei &a, const ei &b) {
	return a.wgt>b.wgt;
}

int dis[10100][60];
vector<edge> pth[10100];
vector<edge> spc[10100];
priority_queue<ei> q;

int main () {
	int n,m,s,l;
	scanf("%d%d%d%d",&n,&m,&s,&l);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c});
	}
	for (int i=0;i<s;i++) {
		scanf("%d%d%d",&a,&b,&c);
		spc[a].push_back(edge{b,c});
	}
	memset(dis,127,sizeof(dis));
	dis[1][0]=0;
	q.push(ei{1,0,0});
	int now,nowT,nowLev;
	while (!q.empty()) {
		now=q.top().idx;
		nowT=q.top().wgt;
		nowLev=q.top().lev;
		q.pop();
		if (nowT>dis[now][nowLev]) continue;
		for (int i=0;i<pth[now].size();i++) {
			if (nowT+pth[now][i].wgt>=dis[pth[now][i].idx][nowLev]) continue;
			dis[pth[now][i].idx][nowLev]=nowT+pth[now][i].wgt;
			q.push(ei{pth[now][i].idx,dis[pth[now][i].idx][nowLev],nowLev});
		}
		if (nowLev==l) continue;
		for (int i=0;i<spc[now].size();i++) {
			if (nowT+spc[now][i].wgt>=dis[spc[now][i].idx][nowLev+1]) continue;
			dis[spc[now][i].idx][nowLev+1]=nowT+spc[now][i].wgt;
			q.push(ei{spc[now][i].idx,dis[spc[now][i].idx][nowLev+1],nowLev+1});
		}
	}
	int ans=2e9;
	for (int i=0;i<=l;i++) {
		ans=min(ans,dis[n][i]);
	}
	printf("%d\n",ans);
	return 0;
}
