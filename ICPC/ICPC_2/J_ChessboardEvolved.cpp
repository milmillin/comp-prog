#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

bool isWall[1010][1010];
int dis[1010][1010];
int di[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

struct ei {
	int r,c,dis;
};

queue<ei> q;

int main () {
	int r,c;
	scanf("%d%d",&r,&c);
	char x;
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			scanf(" %c",&x);
			if (x=='#') isWall[i][j]=true;
		}
	}
	int sr,sc,tr,tc;
	scanf("%d%d%d%d",&sr,&sc,&tr,&tc);
	sr--;
	sc--;
	tr--;
	tc--;
	memset(dis,63,sizeof(dis));
	dis[sr][sc]=0;
	q.push(ei{sr,sc,0});
	
	int rr=max(r,c);
	int nowR,nowC,nowDis,nextR,nextC;
	while (!q.empty()) {
		nowR=q.front().r;
		nowC=q.front().c;
		nowDis=q.front().dis;
		q.pop();
		//printf("%d %d %d\n",nowR,nowC,nowDis);
		if (nowR==tr&&nowC==tc) {
			printf("%d\n",nowDis);
			return 0;
		}

		for (int i=0;i<8;i++) {
			for (int j=1;j<rr;j++) {
				nextR = nowR+(di[i][0]*j);
				nextC = nowC +(di[i][1]*j);
				if (nextR<0||nextR>=r||nextC<0||nextC>=c) break;
				if (isWall[nextR][nextC]) break;
				if (dis[nextR][nextC]<nowDis+1) break;
				if (dis[nextR][nextC]<=nowDis+1) continue;
				dis[nextR][nextC]=nowDis+1;
				//printf("+ %d %d %d\n",nextR,nextC,nowDis);
				q.push(ei{nextR,nextC,nowDis+1});
			}
		}
	}
	printf("-1\n");
	return 0;
}
