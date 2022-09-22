#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct edge {
	int idx,wgt;
};

vector<edge> pth[100100];
int dis[100100][8];

struct ei {
	int idx,wgt,lev;
};

bool operator< (const ei &a,const ei &b) {
	return a.wgt>b.wgt;
}

priority_queue<ei> q;

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int a,b,c;
	memset(dis,127,sizeof(dis));
	printf("%d\n",dis[0][0]*-1);
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		if (c>=-100&&c<0) c=0;
		pth[a].push_back(edge{b,c});
	}
	dis[1][0]=0;
	q.push(ei{1,0,0});
	int now,nowT,nowLev;
	while (!q.empty()) {
		now=q.top().idx;
		nowT=q.top().wgt;
		nowLev=q.top().lev;
		q.pop();
		//printf("%d %d\n",now,nowT);
		if (nowT>dis[now][nowLev]) continue;
		//printf("yay\n");
		for (int i=0;i<(int)pth[now].size();i++) {
			//printf("--%d %d %d\n",pth[now][i].idx,pth[now][i].wgt,dis[pth[now][i].idx][nowLev]);
			if (pth[now][i].wgt<-100) {
				if (nowLev==k) continue;	
				if (nowT>=dis[pth[now][i].idx][nowLev+1]) continue;
				//printf("a\n");
				dis[pth[now][i].idx][nowLev+1]=nowT;
				q.push(ei{pth[now][i].idx,dis[pth[now][i].idx][nowLev+1],nowLev+1});
			} else {
				//printf("%d\n",nowT+pth[now][i].wgt);
				if (nowT+pth[now][i].wgt>=dis[pth[now][i].idx][nowLev]) continue;
				//printf("b\n");
				dis[pth[now][i].idx][nowLev]=nowT+pth[now][i].wgt;
				q.push(ei{pth[now][i].idx,dis[pth[now][i].idx][nowLev],nowLev});
			}
		}
	}
	int ans=2e9+1;
	for (int i=0;i<=k;i++) {
		ans=min(ans,dis[n][i]);
	}
	printf("%d\n",(ans==2e9+1)?-1:ans);
	return 0;
}
