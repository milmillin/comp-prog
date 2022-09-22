#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

bool isWall[1010][1010];
bool isTel[1010][1010];
int rr[1010][1010];
int cc[1010][1010];
int dis[1010][1010];

int di[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
int de[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};

struct ei {
	int r,c,dis;
};

bool operator< (const ei &a, const ei &b) {
	return a.dis>b.dis;
}


void f() {
	memset(isWall,0,sizeof(isWall));
	memset(isTel,0,sizeof(isTel));
	memset(rr,0,sizeof(rr));
	memset(cc,0,sizeof(cc));
	memset(dis,63,sizeof(dis));

	priority_queue<ei> qq;
	int r,c,sr,sc,fr,fc,b,t;
	scanf("%d%d%d%d%d%d%d%d",&r,&c,&sr,&sc,&fr,&fc,&b,&t);
	sr--;
	sc--;
	fr--;
	fc--;

	int aa,bb,mm,nn;
	for (int i=0;i<b;i++) {
		scanf("%d%d",&aa,&bb);
		aa--;
		bb--;
		isWall[aa][bb]=true;
	}
	for (int i=0;i<t;i++) {
		scanf("%d%d%d%d",&aa,&bb,&mm,&nn);
		aa--;
		bb--;
		mm--;
		nn--;
		isTel[aa][bb]=true;
		rr[aa][bb]=mm;
		cc[aa][bb]=nn;
	}
	dis[sr][sc]=0;
	qq.push(ei{sr,sc,0});
	int nowR,nowC,nextR,nextC,nowDis;
	while (!qq.empty()) {
		nowR = qq.top().r;
		nowC = qq.top().c;
		nowDis = qq.top().dis;
		qq.pop();
		//printf("-- %d %d %d\n",nowR,nowC,nowDis);
		if (nowDis>dis[nowR][nowC]) continue;
		dis[nowR][nowC]=nowDis;
		if (nowR==fr&&nowC==fc) {
			printf("%d\n",nowDis);
			return;
		}
		//printf("yay\n");
		if (isTel[nowR][nowC]) {
			//printf("fck\n");
			nextR = rr[nowR][nowC];
			nextC = cc[nowR][nowC];
			if (dis[nextR][nextC]>nowDis) {
				dis[nextR][nextC]=nowDis;
				qq.push(ei{nextR,nextC,nowDis});
			}
			continue;
		}
		for (int i=0;i<4;i++) {
			nextR = nowR +di[i][0];
			nextC = nowC +di[i][1];
			//printf("--fck\n");
			if (nextR<0||nextR>=r||nextC<0||nextC>=c) continue;
			if (isWall[nextR][nextC]) continue;
			if (dis[nextR][nextC]<=nowDis+101) continue;
			dis[nextR][nextC]=nowDis+101;
			qq.push(ei{nextR,nextC,nowDis+101});
		}
		for (int i=0;i<4;i++) {
			nextR = nowR +de[i][0];
			nextC = nowC +de[i][1];
			if (nextR<0||nextR>=r||nextC<0||nextC>=c) continue;
			if (isWall[nextR][nextC]) continue;
			if (dis[nextR][nextC]<=nowDis+151) continue;
			dis[nextR][nextC]=nowDis+151;
			qq.push(ei{nextR,nextC,nowDis+151});
		}
	}
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
