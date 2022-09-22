#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct point {
	int r,c;
	int dr,dc;
	int dis;

	point add(int rr,int cc) const {
		int nr=dr+rr;
		int nc=dc+cc;
		return point{r+rr,c+cc,nr,nc,nr*nr+nc*nc};
	}
};

bool operator< (const point &a, const point &b) {
	return a.dis>b.dis;
}

struct pp {
	int r,c;
	int mn;
};

bool operator< (const pp &a, const pp &b) {
	return a.mn<b.mn;
}


int dis[1010][1010];
int di[8][2]={{0,-1},{0,1},{-1,0},{1,0},{-1,-1},{-1,1},{1,-1},{1,1}};

int dis2[1010][1010];

int main () {
	int r,c;
	scanf("%d%d",&r,&c);
	int sr,sc,tr,tc;
	scanf("%d%d%d%d",&sr,&sc,&tr,&tc);
	sr--;
	sc--;
	tr--;
	tc--;
	int n;
	scanf("%d",&n);
	int x,y;
	priority_queue<point> q;
	memset(dis,63,sizeof(dis));
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x,&y);
		x--;
		y--;
		q.push(point{x,y,0,0,0});
		dis[x][y]=0;
	}
	point now;
	while (!q.empty()) {
		now = q.top();
		q.pop();
		//if (dis[now.r][now.c]<now.dis) continue;
		for (int i=0;i<8;i++) {
			point next = now.add(di[i][0],di[i][1]);
			if (next.r<0||next.r>=r||next.c<0||next.c>=c) continue;
			if (dis[next.r][next.c]<=next.dis) continue;
			dis[next.r][next.c]=next.dis;
			q.push(next);
		}
	}
	//memset(dis2,63,sizeof(dis2));
	dis2[sr][sc]=dis[sr][sc];
	priority_queue<pp> qq;
	qq.push(pp{sr,sc,dis[sr][sc]});
	pp noww;
	while (!qq.empty()) {
		noww = qq.top();
		qq.pop();
		//if (dis2[noww.r][noww.c]>noww.mn) continue;
		for (int i=0;i<4;i++) {
			pp next = pp{noww.r+di[i][0],noww.c+di[i][1],0};
			if (next.r<0||next.r>=r||next.c<0||next.c>=c) continue;
			next.mn = min(noww.mn,dis[next.r][next.c]);
			if (dis2[next.r][next.c]>=next.mn) continue;
			dis2[next.r][next.c]=next.mn;
			qq.push(next);
		}
	}
	printf("%d\n",dis2[tr][tc]);
	return 0;
}
