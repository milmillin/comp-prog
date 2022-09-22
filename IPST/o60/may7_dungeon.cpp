#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

bool block[1010][1010];
int dis[1010][1010];

struct tt{
	int x1,y1,x2,y2;
};

struct ei {
	int x,y,dis;
};

bool operator< (const ei &a, const ei &b) {
	return a.dis>b.dis;
}

int di[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int dx[4][2]={{1,1},{1,-1},{-1,1},{-1,-1}};

void f() {
	int w,h,sx,sy,gx,gy,b,t;
	scanf("%d%d%d%d%d%d%d%d",&w,&h,&sx,&sy,&gx,&gy,&b,&t);
	
	memset(block,0,sizeof(block));	
	memset(dis,63,sizeof(dis));

	int aa,bb;
	for (int i=0;i<b;i++) {
		scanf("%d%d",&aa,&bb);
		block[aa][bb]=true;
	}
	vector<tt> tp;
	int cc,dd;
	for (int i=0;i<t;i++) {
		scanf("%d%d%d%d",&aa,&bb,&cc,&dd);
		tp.push_back(tt{aa,bb,cc,dd});
		tp.push_back(tt{cc,dd,aa,bb});
	}	
	priority_queue<ei> q;
	q.push(ei{sx,sy,0});
	dis[sx][sy]=0;

	int nowx,nowy,nowdis,nextx,nexty;
	while (!q.empty()) {
		auto now=q.top();
		q.pop();
		nowx=now.x;
		nowy=now.y;
		nowdis=now.dis;
		if (dis[nowx][nowy]<nowdis) continue;
		for (int i=0;i<4;i++) {
			nextx=nowx+di[i][0];
			nexty=nowy+di[i][1];
			if (nextx<=0||nextx>w||nexty<=0||nexty>h) continue;
			if (block[nextx][nexty]) continue;
			if (dis[nextx][nexty]<=dis[nowx][nowy]+101) continue;
			dis[nextx][nexty]=dis[nowx][nowy]+101;
			q.push(ei{nextx,nexty,dis[nextx][nexty]});
		}
		for (int i=0;i<4;i++) {
			nextx=nowx+dx[i][0];
			nexty=nowy+dx[i][1];
			if (nextx<=0||nextx>w||nexty<=0||nexty>h) continue;
			if (block[nextx][nexty]) continue;
			if (dis[nextx][nexty]<=dis[nowx][nowy]+151) continue;
			dis[nextx][nexty]=dis[nowx][nowy]+151;
			q.push(ei{nextx,nexty,dis[nextx][nexty]});
		}
		for (auto &i:tp) {
			if (nowx==i.x1&&nowy==i.y1) {
				if (dis[i.x2][i.y2]<=dis[nowx][nowy]) break;
				dis[i.x2][i.y2]=dis[nowx][nowy];
				q.push(ei{i.x2,i.y2,dis[i.x2][i.y2]});
				break;
			}
		}
	}
	//for (int i=1;i<=h;i++) {
		//for (int j=1;j<=w;j++) {
			//printf("%d ",dis[j][i]);
		//}
		//printf("\n");
	//}
	printf("%d\n",dis[gx][gy]);
}

int main () {
	int l;
	scanf("%d",&l);
	while (l--) {
		f();
	}
	return 0;
}
