#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct edge {
	int from,to,wgt;
};

struct ee {
	int from,to,wgt,d;
};

bool operator< (const edge &a, const edge &b) {
	if (a.from!=b.from) return a.from<b.from;
	return a.to<b.to;
}

bool operator< (const ee &a, const ee &b) {
	return a.wgt>b.wgt;
}

int tbl[10010][10010];
vector<edge> chd;
priority_queue<ee> q;
bool sel[10010];
int par[10010];
int dis[10010];

int main () {
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<i;j++) {
			scanf("%d",&tbl[i][j]);
		}
		for (int j=i+1;j<=n;j++) {
			scanf("%d",&tbl[i][j]);
		}
	}
	for (int i=2;i<=n;i++) {
		q.push(ee{1,i,tbl[1][i],1});
	}
	int nowf,nowt,nowDis,nowD;
	sel[1]=true;
	dis[1]=0;
	bool isDone=false;
	while (!q.empty()) {
		nowf=q.top().from;
		nowt=q.top().to;
		nowDis=q.top().wgt;
		nowD=q.top().d;
		q.pop();
		if (sel[nowt]) {
			if (!isDone) {
				if (dis[nowf]>dis[nowt]) swap(nowf,nowt);
				//printf("--%d %d %d %d %d\n",nowf,nowt,par[nowt],tbl[nowf][par[nowt]],tbl[par[nowt]][nowt]);
				if (tbl[nowf][par[nowt]]+tbl[par[nowt]][nowt]==nowDis) continue;
				chd.push_back(edge{min(nowf,nowt),max(nowt,nowf),nowDis});
				isDone=true;
			}
			continue;
		}
		sel[nowt]=true;
		//chd[nowf].push_back(edge{nowt,nowDis});
		//printf("**%d %d\n",nowf,nowt);
		chd.push_back(edge{min(nowf,nowt),max(nowt,nowf),nowDis});
		par[nowt]=nowf;
		dis[nowt]=nowD;
		//printf("--%d\n",par[nowt]);
		for (int i=1;i<=n;i++) {
			if (i==nowt) continue;
			if (sel[i]) continue;
			q.push(ee{nowt,i,tbl[nowt][i],nowD+1});
		}
	}
	sort(chd.begin(),chd.end());
	for (int i=0;i<(int)chd.size();i++) {
		printf("%d %d %d\n",chd[i].from,chd[i].to,chd[i].wgt);
	}
	return 0;
}
