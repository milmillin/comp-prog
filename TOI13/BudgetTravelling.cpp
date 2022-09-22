#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct edge {
	int to,dis;
};

bool operator< (const edge &a, const edge &b) {
	if (a.dis!=b.dis) return a.dis>b.dis;
	return a.to>b.to;
}

vector<edge> pth[10100];

int dis[10100];
int dis2[10100];

priority_queue<edge> q;

int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	int x,y,z;
	scanf("%d%d%d",&x,&y,&z);
	int u,v,d;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&u,&v,&d);
		pth[u].push_back(edge{v,d});
		pth[v].push_back(edge{u,d});
	}
	memset(dis,63,sizeof(dis));
	dis[x]=0;
	//printf("%d\n",dis[1]);
	q.push(edge{x,0});
	int now,nowDis;
	while (!q.empty()) {
		now=q.top().to;
		nowDis=q.top().dis;
		q.pop();
		for (int i=0;i<(int)pth[now].size();i++) {
			if (dis[pth[now][i].to]<=nowDis+pth[now][i].dis) continue;
			if (nowDis+pth[now][i].dis>z) continue;
			dis[pth[now][i].to]=nowDis+pth[now][i].dis;
			q.push(edge{pth[now][i].to,dis[pth[now][i].to]});
		}
	}
	if (dis[y]!=1061109567) {
		printf("%d %d %d\n",y,dis[y],0);
		return 0;
	}
	memset(dis2,63,sizeof(dis2));
	while (!q.empty()) q.pop();
	
	dis2[y]=0;
	q.push(edge{y,0});
	while (!q.empty()) {
		now=q.top().to;
		nowDis=q.top().dis;
		q.pop();
		if (dis[now]!=1061109567) {
			printf("%d %d %d\n",now,dis[now],nowDis);
			return 0;
		}
		for (int i=0;i<(int)pth[now].size();i++) {
			if (dis2[pth[now][i].to]<=nowDis+pth[now][i].dis) continue;
			dis2[pth[now][i].to]=nowDis+pth[now][i].dis;
			q.push(edge{pth[now][i].to,dis2[pth[now][i].to]});
		}
	}

	return 0;
}
