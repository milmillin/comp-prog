#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int to,dis;
};

struct pp {
	int a,b;
};

bool operator< (const edge &a, const edge &b) {
	return a.dis>b.dis;
}

vector<edge> pth[200];
int dis[200];
int from[200];
vector<pp> route;

priority_queue<edge> q;

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(edge{b,c});
		pth[b].push_back(edge{a,c});
		route.push_back(pp{a,b});
	}
	q.push(edge{1,0});
	memset(dis,63,sizeof(dis));
	dis[1]=0;
	int now,nowDis;
	while (!q.empty()) {
		now=q.top().to;
		nowDis=q.top().dis;
		q.pop();
		for (int i=0;i<(int)pth[now].size();i++) {
			if (dis[pth[now][i].to]<=dis[now]+pth[now][i].dis) continue;
			dis[pth[now][i].to]=dis[now]+pth[now][i].dis;
			from[pth[now][i].to]=now;
			q.push(edge{pth[now][i].to,dis[pth[now][i].to]});
		}
	}
	int reDis=dis[n];
	//int cur=n;
	//while (cur!=1) {
		//route.push_back(pp{from[cur],cur});
		//cur=from[cur];
	//}
	
	int aa,bb;
	int mxDis=0;
	int pDis;
	for (int j=0;j<(int)route.size();j++) {
		aa=route[j].a;
		bb=route[j].b;
		memset(dis,63,sizeof(dis));
		//while (!q.empty()) q.pop();
		dis[1]=0;
		q.push(edge{1,0});
		while (!q.empty()) {
			now=q.top().to;
			nowDis=q.top().dis;
			q.pop();
			for (int i=0;i<(int)pth[now].size();i++) {
				pDis=pth[now][i].dis;
				if ((aa==now&&bb==pth[now][i].to)||(aa==pth[now][i].to&&bb==now)) pDis*=2;
				if (dis[pth[now][i].to]<=dis[now]+pDis) continue;
				dis[pth[now][i].to]=dis[now]+pDis;
				q.push(edge{pth[now][i].to,dis[pth[now][i].to]});
			}
		}
		mxDis=max(mxDis,dis[n]);
		//printf("%d %d %d\n",dis[n],aa,bb);
		//for (int i=1;i<=n;i++) {
			//printf("-- %d %d\n",i,dis[i]);
		//}
	}
	//printf("%d\n",mxDis);
	printf("%d\n",mxDis-reDis);
	return 0;
}
