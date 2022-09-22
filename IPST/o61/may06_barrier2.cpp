#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int tbl[600][600];
int dis[510][510][510];

struct ei {
	int r,c,org,dis;
};

bool operator< (const ei &a, const ei &b) {
	return a.dis>b.dis;
}

int di[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

int main () {
	int r,c;
	scanf("%d%d",&r,&c);
	int x,y;
	scanf("%d%d",&x,&y);
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			scanf("%d",&tbl[i][j]);
		}
	}
	tbl[x][y]=1e9;
	priority_queue<ei> q;
	int nowr,nowc,noworg,nowdis,nextr,nextc;
	//for (int i=x-1;i>=-) {
	memset(dis,63,sizeof(dis));
	for (int i=x-1;i>0;i--) {
		dis[i][y][i]=tbl[i][y];
		q.push(ei{i,y,i,dis[i][y][i]});	
	}
	while (!q.empty()) {
		nowr=q.top().r;
		nowc=q.top().c;
		nowdis=q.top().dis;
		noworg=q.top().org;
		q.pop();
		//printf("%d %d\n",nowr,nowc);
		for (int j=0;j<4;j++) {
			nextr=nowr+di[j][0];
			nextc=nowc+di[j][1];
			if (nextr<=0||nextr>r||nextc<y||nextc>c) continue;
			if (dis[nextr][nextc][noworg]<=dis[nowr][nowc][noworg]+tbl[nextr][nextc]) continue;
			dis[nextr][nextc][noworg]=dis[nowr][nowc][noworg]+tbl[nextr][nextc];
			q.push(ei{nextr,nextc,noworg,dis[nextr][nextc][noworg]});
		}
	}
	for (int j=x+1;j<=r;j++) {
		//rec[j][i]=dis[j][y];		
		for (int i=x-1;i>0;i--) {
			q.push(ei{j,y,i,dis[j][y][i]});
		}
	}
	for (int i=x-1;i>=1;i--) dis[i][y][i]=1e9;
	while (!q.empty()) {
		nowr=q.top().r;
		nowc=q.top().c;
		nowdis=q.top().dis;
		noworg=q.top().org;
		q.pop();
		if (nowr==noworg&&nowc==y-1) {
			//ans=min(ans,nowdis-tbl[nowr][nowc]);
			printf("%d\n",nowdis);
			break;
		}
		if (nowr==noworg-1&&nowc==y) {
			printf("%d\n",nowdis);
			break;
		}
		if (nowr==noworg+1&&nowc==y) {
			printf("%d\n",nowdis);
			break;
		}
		for (int j=0;j<4;j++) {
			nextr=nowr+di[j][0];
			nextc=nowc+di[j][1];
			if (nextr<=0||nextr>r||nextc<=0||nextc>y) continue;
			if (dis[nextr][nextc][noworg]<=dis[nowr][nowc][noworg]+tbl[nextr][nextc]) continue;
			dis[nextr][nextc][noworg]=dis[nowr][nowc][noworg]+tbl[nextr][nextc];
			q.push(ei{nextr,nextc,noworg,dis[nextr][nextc][noworg]});
		}
	}
	return 0;
}
