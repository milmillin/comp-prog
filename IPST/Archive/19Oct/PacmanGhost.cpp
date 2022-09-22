#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

typedef struct {
	int r,c,t;
} cell;

bool operator< (const cell &a, const cell &b) {
	return a.t>b.t;
}

int tbl[105][105];
bool visit[105][105];
int di[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

void f() {
	int R,C,n,T,r,c;
	scanf("%d%d%d%d%d%d",&R,&C,&n,&T,&r,&c);
	priority_queue<cell> q;
	memset(tbl,127,sizeof(tbl));
	memset(visit,0,sizeof(visit));
	//q.push(cell{r,c,0});
	int x,y,z;
	for (int i=0;i<n;i++) {
		scanf("%d%d%d",&x,&y,&z);
		q.push(cell{y,z,x});
	}
	char xx;
	for (int i=0;i<R;i++) {
		for (int j=0;j<C;j++) {
			scanf(" %c",&xx);
			if (xx=='#') tbl[i][j]=-2e9;
		}
	}
	int nowR,nowC,nowT,nextR,nextC;
	while (!q.empty()) {
		nowR=q.top().r;
		nowC=q.top().c;
		nowT=q.top().t;
		q.pop();
		if (nowT>tbl[nowR][nowC]) continue;
		tbl[nowR][nowC]=nowT;
		if (nowT>T+2) break;
		for (int i=0;i<4;i++) {
			nextR=nowR+di[i][0];
			nextC=nowC+di[i][1];
			if (nextR<0||nextR>=R||nextC<0||nextC>=C) continue;
			if (tbl[nextR][nextC]<=nowT+1) continue;
			tbl[nextR][nextC]=nowT+1;
			q.push(cell{nextR,nextC,nowT+1});
		}
	}
	queue<cell> qq;
	qq.push(cell{r,c,0});
	int maxT=-1;
	while (!qq.empty()) {
		nowR=qq.front().r;
		nowC=qq.front().c;
		nowT=qq.front().t;
		qq.pop();
		//printf("%d %d\n",nowR,nowC);
		if(tbl[nowR][nowC]<=nowT) continue;
		maxT=max(tbl[nowR][nowC]-1,maxT);
		visit[nowR][nowC]=true;
		if (nowT>T+2) break;
		for (int i=0;i<4;i++) {
			nextR=nowR+di[i][0];
			nextC=nowC+di[i][1];
			if (nextR<0||nextR>=R||nextC<0||nextC>=C) continue;
			if (tbl[nextR][nextC]<=nowT+1) continue;
			if (visit[nextR][nextC]) continue;
			visit[nextR][nextC]=true;
			qq.push(cell{nextR,nextC,nowT+1});
		}
	}
	if (maxT>=T) printf("YES\n");
	else printf("NO\n");
	//printf("%d\n",maxT);
	/*
	for (int i=0;i<R;i++) {
		for (int j=0;j<C;j++) {
			printf("%d ",tbl[i][j]);
		}
		printf("\n");
	}
	*/
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
